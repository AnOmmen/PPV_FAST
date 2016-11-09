#include "Interpolator.h"



Interpolator::Interpolator()
{
	m_currBlendTime = 0;
}


Interpolator::~Interpolator()
{
}

Bone * Interpolator::GetCurrentWorld(int & _num)
{
	return &m_world[_num];
}

float Interpolator::GetTime()
{
	return m_currBlendTime;
}

void Interpolator::SetAnimation(const Animation * _anim)
{
	m_animation = _anim;
}

void Interpolator::SetCurrTime(float _time)
{

	m_currBlendTime = _time;
}

void Interpolator::SetTotalTime(float _time)
{
	m_totalBlendTime = _time;
}

KeyFrame Interpolator::Update(float _time)
{
	KeyFrame nextFrame;
	KeyFrame prevFrame;
	prevFrame.m_time = 0;

	float frameTime = 0;
	float tweenTime = 0;
	tweenTime = m_animation->GetFrame(1)->m_time - m_animation->GetFrame(0)->m_time;

	m_currFrame.m_bones.clear();
	SetTotalTime(m_animation->m_totaltime);
	if (m_currBlendTime + _time > m_totalBlendTime)
	{
		m_currBlendTime = (m_currBlendTime + _time) - m_totalBlendTime;
		prevFrame.m_time = 0;// m_animation->GetFrame(m_animation->GetNumKeyFrames() - 1)->m_time;
		prevFrame.m_bones = m_animation->GetFrame(m_animation->GetNumKeyFrames()-1)->m_bones;

		nextFrame.m_bones = m_animation->GetFrame(0)->m_bones;
		nextFrame.m_time = m_animation->GetFrame(0)->m_time;
		/*prevFrame = *m_animation->GetFrame(0);
		nextFrame = *m_animation->GetFrame(1);*/
	}
	else
	{
		SetCurrTime(m_currBlendTime + _time);
		for (unsigned int i = 0; i < m_animation->GetNumKeyFrames(); i++)
		{
			if (m_animation->GetFrame(i)->m_time > m_currBlendTime)
			{
				nextFrame.m_time = m_animation->GetFrame(i)->m_time;
				nextFrame.m_bones = m_animation->GetFrame(i)->m_bones;
				break;
			}
			else if (m_animation->GetFrame(i)->m_time == m_currBlendTime)
			{
				m_currFrame.m_bones = m_animation->GetFrame(i)->m_bones;
				m_currFrame.m_time = m_animation->GetFrame(i)->m_time;

				return m_currFrame;
			}

			prevFrame.m_time = m_animation->GetFrame(i)->m_time;
			prevFrame.m_bones = m_animation->GetFrame(i)->m_bones;

		}
	}

	//DO THE MATHS
	frameTime = m_currBlendTime - prevFrame.m_time;
	float ratio = frameTime / tweenTime;
	m_currFrame = Interpolate(prevFrame, nextFrame, ratio);

	m_currFrame.m_time = GetTime();
	return m_currFrame;
}

KeyFrame Interpolator::Interpolate(KeyFrame _prevFrame, KeyFrame _nextFrame, float _ratio)
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
