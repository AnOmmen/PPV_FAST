#pragma once
#include "Interpolator.h"
#include "AnimationSet.h"
class Blender
{
public:
	AnimationSet* m_animationContainer;
	BlendInfo* m_blend;
	std::vector<XMMATRIX> m_boneOffsetArray;
	Interpolator* m_currAnim;
	Interpolator* m_nextAnim;
	Blender();
	~Blender();
	const XMMATRIX* GetSkinningMatrix();
	void SetAnimSet(std::string _key);
	bool SetNextAnim(BLEND_TYPE _type, int _animKey);
	void Update(float _time);
};

