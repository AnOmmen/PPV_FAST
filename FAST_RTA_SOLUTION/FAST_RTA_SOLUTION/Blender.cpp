#include "Blender.h"



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

const DirectX::XMMATRIX * Blender::GetSkinningMatrix()
{
	return nullptr;
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
	//set buffers, dave already does this somewhere else
}
