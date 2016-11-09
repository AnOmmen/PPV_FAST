#include "Blender.h"
#include "BindPose.h"


Blender::Blender(const Animation* anim)
{
	//Set interpolators
	// animation
	m_currAnim = new Interpolator();
	m_currAnim->SetAnimation(anim);


}


Blender::~Blender()
{
	delete m_currAnim;
}

KeyFrame Blender::GetUpdatedKeyFrame() const
{
	return m_updatedKeyFrame;
}

 DirectX::XMMATRIX * Blender::GetSkinningMatrix()
{
	return &m_boneOffsetArray[0];
}

void Blender::SetAnimSet(std::string _key)
{
	
}

bool Blender::SetNextAnim(BLEND_TYPE _type, int _animKey)
{
	return false;
}

void Blender::Update(float _time)
{
	//call update on interpolator(s)

	m_currAnim->Update(_time);
	m_boneOffsetArray.clear();
	for (size_t i = 0; i < m_animationContainer->GetDefaultAnimation()->GetNumBones(); i++)
	{
		XMMATRIX bpi = XMLoadFloat4x4(&m_animationContainer->GetBindPose()->GetBindPose()[i]);
		XMMATRIX notworld = XMLoadFloat4x4(&m_currAnim->m_currFrame.m_bones[i].m_world);
		XMMATRIX mult = XMMatrixMultiply(bpi, notworld);
		m_boneOffsetArray.push_back(mult);
	}
	

	//set buffers, dave already does this somewhere else
}
