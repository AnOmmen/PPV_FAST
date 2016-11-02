#pragma once
#include <vector>
#include "StructsEnumsDefines.h"



class Animation
{
	ANIM_TYPE m_animType;
	std::vector<KeyFrame> m_keyFrames;
	unsigned int m_numBones;
	float m_totaltime;
public:
	Animation();
	~Animation();
	const KeyFrame* GetFrame(int _index);
	unsigned int GetNumKeyFrames() const;
	unsigned int GetNumBones() const;
	void Init(KeyFrame const *_keyFrames, unsigned int _numKeyFrames, ANIM_TYPE _animType);
};

