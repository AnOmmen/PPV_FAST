#pragma once
#include <vector>
#include "StructsEnumsDefines.h"
using namespace DirectX;



class Animation
{
public:
	ANIM_TYPE m_animType;
	std::vector<KeyFrame> m_bones;
	int m_numKeyframes;
	float m_totaltime;
	Animation();
	~Animation();
	const Bone* GetFrame(int _index);
	int GetNumBones();
	void Init(int _num, ANIM_TYPE _type);
};

