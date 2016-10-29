#include "Interpolator.h"



Interpolator::Interpolator()
{
}


Interpolator::~Interpolator()
{
}

Bone * Interpolator::GetCurrentWorld(int & _num)
{
	return nullptr;
}

float Interpolator::GetTime()
{
	return 0.0f;
}

void Interpolator::SetAnimation(const Animation * _anim)
{
}

void Interpolator::SetTime(float _time)
{
}

ANIM_TYPE Interpolator::Update(float _time)
{
	return ANIM_TYPE();
}
