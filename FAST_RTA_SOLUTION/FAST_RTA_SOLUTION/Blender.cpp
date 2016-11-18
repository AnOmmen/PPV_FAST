#include "Blender.h"
#include "BindPose.h"


Blender::Blender(const Animation* anim)
{
	//Set interpolators
	// animation
	m_currAnim = new Interpolator();
	m_nextAnim = nullptr;
	m_currAnim->SetAnimation(anim);
	m_totalBlendTime = 0.2;
	m_currBlendTime = 0;
}


Blender::~Blender()
{
	delete m_currAnim;
	delete m_nextAnim;
}

KeyFrame Blender::GetUpdatedKeyFrame() const
{
	return m_updatedKeyFrame;
}

 DirectX::XMMATRIX * Blender::GetSkinningMatrix()
{
	return &m_boneOffsetArray[0];
}

void Blender::SetAnimSet(AnimationSet* animSet)
{
	m_animationContainer = animSet;
}

bool Blender::SetNextAnim(const Animation* _anim)
{
	if (nullptr == _anim)
	{
		return false;
	}
	m_nextAnim = new Interpolator();
	m_nextAnim->SetAnimation(_anim);
	return true;
}

void Blender::Update(float _time)
{
	m_currAnim->Update(_time);
	m_updatedKeyFrame = m_currAnim->m_currFrame;
	//call update on interpolator(s)
	if (m_nextAnim != nullptr && m_nextAnim != m_currAnim)
	{
		m_currBlendTime += _time;
		m_nextAnim->Update(_time);
		float ratio = m_currBlendTime / m_totalBlendTime;
		m_updatedKeyFrame = Interpolate(m_currAnim->m_currFrame, m_nextAnim->m_currFrame, ratio);
		if (m_currBlendTime > m_totalBlendTime)
		{

			delete m_currAnim;
			m_currAnim = new Interpolator();
			m_currAnim->SetAnimation(m_nextAnim->m_animation);
			m_currAnim->SetCurrTime(m_nextAnim->GetTime());
			delete m_nextAnim;
			//m_nextAnim = new Interpolator();
			m_nextAnim = nullptr;
			m_currBlendTime = 0;
		}
		
	}

	m_boneOffsetArray.clear();
	for (size_t i = 0; i < m_updatedKeyFrame.m_bones.size(); i++)
	{
		XMMATRIX bpi = XMLoadFloat4x4(&m_animationContainer->GetBindPose()->GetBindPose()[i]);
		XMMATRIX notworld = XMLoadFloat4x4(&m_updatedKeyFrame.m_bones[i].m_world);
		XMMATRIX mult = XMMatrixMultiply(bpi, notworld);
		m_boneOffsetArray.push_back((mult));
	}
	

	
}

KeyFrame Blender::Interpolate(KeyFrame _prevFrame, KeyFrame _nextFrame, float _ratio)
{
	KeyFrame set;
	int numBones = _prevFrame.m_bones.size();
	for (int i = 0; i < numBones; i++)
	{
		DirectX::XMVECTOR scaleCur;
		DirectX::XMVECTOR rotationCur;
		DirectX::XMVECTOR positionCur;

		DirectX::XMVECTOR nextScale;
		DirectX::XMVECTOR nextQuat;
		DirectX::XMVECTOR nextTrans;

		DirectX::XMMATRIX prevMat;
		DirectX::XMMATRIX nextMat;

		prevMat = DirectX::XMLoadFloat4x4(&_prevFrame.m_bones[i].m_world);
		nextMat = DirectX::XMLoadFloat4x4(&_nextFrame.m_bones[i].m_world);
		DirectX::XMMatrixDecompose(&scaleCur, &rotationCur, &positionCur, prevMat);
		DirectX::XMMatrixDecompose(&nextScale, &nextQuat, &nextTrans, nextMat);
		DirectX::XMVECTOR currRot = DirectX::XMQuaternionSlerp(rotationCur, nextQuat, _ratio);
		DirectX::XMVECTOR currScale = DirectX::XMVectorLerp(scaleCur, nextScale, _ratio);
		DirectX::XMVECTOR currPos = DirectX::XMVectorLerp(positionCur, nextTrans, _ratio);

		DirectX::XMMATRIX tempCatch = DirectX::XMMatrixAffineTransformation(currScale, DirectX::XMVectorZero(), currRot, currPos);
		Bone newBone;
		DirectX::XMStoreFloat4x4(&newBone.m_world, tempCatch);
		set.m_bones.push_back(newBone);
	}
	return set;
}
