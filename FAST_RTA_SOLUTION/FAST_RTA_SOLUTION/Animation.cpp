#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

const KeyFrame * Animation::GetFrame(int _index)
{
	return &m_keyFrames[_index];
}

unsigned int Animation::GetNumKeyFrames() const
{
	return m_keyFrames.size();
}

unsigned int Animation::GetNumBones() const
{
	return m_numBones;
}

void Animation::Init(KeyFrame const *_keyFrames, unsigned int _numKeyFrames, ANIM_TYPE _animType)
{
	if (NULL != _numKeyFrames && nullptr != _keyFrames)
	{
		m_numBones = _keyFrames[0].m_bones.size();
		m_keyFrames.resize(_numKeyFrames);
		for (unsigned int i = 0; i < _numKeyFrames; ++i)
			m_keyFrames[i].m_bones.resize(m_numBones);
		memcpy_s(&m_keyFrames[0], m_keyFrames.size(), _keyFrames, _numKeyFrames);
	}
}
