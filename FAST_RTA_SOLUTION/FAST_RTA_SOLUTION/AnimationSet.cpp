#include "AnimationSet.h"



AnimationSet::AnimationSet()
{
}


AnimationSet::~AnimationSet()
{
}

bool AnimationSet::AddAnimation(FILE * _file)
{
	return false;
}

bool AnimationSet::AddBindPose(const BindPose * _pose)
{
	return false;
}

const Animation * AnimationSet::GetAnimation(int _key)
{
	return nullptr;
}

const BlendInfo * AnimationSet::GetBlendInfo(int _animationFrom, int _animationTo)
{
	return nullptr;
}

const Animation * AnimationSet::GetDefaultAnimation()
{
	return nullptr;
}
