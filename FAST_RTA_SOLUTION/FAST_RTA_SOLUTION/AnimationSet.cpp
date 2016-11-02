#include "AnimationSet.h"



AnimationSet::AnimationSet() : m_bindPose(nullptr), m_defaultAnim(NULL)
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
	if (nullptr != _pose)
	{
		m_bindPose = _pose;
		return true;
	}
	return false;
}

unsigned int AnimationSet::GetAnimationCount() const
{
	return m_animations.size();
}

const Animation * AnimationSet::GetAnimation(int _key) const
{
	if (_key < m_animations.size())
		return &m_animations[_key];
	return nullptr;
}

const BlendInfo * AnimationSet::GetBlendInfo(int _animationFrom, int _animationTo)
{
	return nullptr;
}

const BindPose * AnimationSet::GetBindPose() const
{
	return m_bindPose;
}

const Animation * AnimationSet::GetDefaultAnimation()
{
	return nullptr;
}
