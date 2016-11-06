#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

const KeyFrame * Animation::GetFrame(int _index) const
{
	return &m_keyFrames[_index];
}

float Animation::GetTotalTime() const
{
	return m_totaltime;
}

unsigned int Animation::GetNumKeyFrames() const
{
	return m_keyFrames.size();
}

unsigned int Animation::GetNumBones() const
{
	return m_numBones;
}

void Animation::Init(std::vector<KeyFrame> &_keyFrames, ANIM_TYPE _animType)
{
	m_keyFrames = _keyFrames;
	m_animType = _animType;
	m_numBones = m_keyFrames[0].m_bones.size();
	m_totaltime = m_keyFrames[m_keyFrames.size() - 1].m_time - m_keyFrames[0].m_time;
}
