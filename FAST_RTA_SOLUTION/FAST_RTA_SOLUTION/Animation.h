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
	const KeyFrame* GetFrame(int _index) const;
	unsigned int GetNumKeyFrames() const;
	unsigned int GetNumBones() const;
	// COPIES INFORMATION DOES NOT STORE IT DYNAMICALLY //
	void Init(std::vector<KeyFrame> &_keyFrames, ANIM_TYPE _animType);
};

