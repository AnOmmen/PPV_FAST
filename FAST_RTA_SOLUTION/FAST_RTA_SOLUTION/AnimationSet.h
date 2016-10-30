#pragma once
#include <vector>
#include "Animation.h"
#include "BindPose.h"

class AnimationSet
{
public:
	std::vector<Animation> m_animations;
	const BindPose* m_bindPose;
	std::vector<std::vector<BlendInfo> > m_blendTimes;
	int m_defaultAnim;
	AnimationSet();
	~AnimationSet();
	bool AddAnimation(FILE* _file);
	bool AddBindPose(const BindPose* _pose);
	const Animation* GetAnimation(int _key);
	const BlendInfo* GetBlendInfo(int _animationFrom, int _animationTo);
	const Animation* GetDefaultAnimation();
};

