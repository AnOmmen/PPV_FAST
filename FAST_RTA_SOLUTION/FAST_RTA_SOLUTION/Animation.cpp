#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

const Bone * Animation::GetFrame(int _index)
{
	return &Bone();
}

int Animation::GetNumBones()
{
	return 0;
}

void Animation::Init(int _num, ANIM_TYPE _type)
{
	m_numKeyframes = _num;
	m_animType = _type;
}
