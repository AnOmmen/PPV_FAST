#include "AnimationSet.h"
#include "../FAST_BINARY_IO/FASTBinaryIO.h"


AnimationSet::AnimationSet() : m_bindPose(nullptr), m_defaultAnim(NULL)
{
}


AnimationSet::~AnimationSet()
{
}

bool AnimationSet::AddAnimation(FILE * _file)
{
	FASTBinaryIO::FASTFile *fastFile = FASTBinaryIO::Create(FASTBinaryIO::WRITE);
	std::string thing = "hi-oh!";
	unsigned long num;
	FASTBinaryIO::Open(fastFile, "../guyo.txt");
	FASTBinaryIO::Write(fastFile, thing.size() + 1, thing.c_str(), num);
	FASTBinaryIO::Close(fastFile);
	FASTBinaryIO::Destroy(fastFile);

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
