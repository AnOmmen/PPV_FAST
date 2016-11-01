#include "Blender.h"



Blender::Blender()
{
}


Blender::~Blender()
{
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
}
