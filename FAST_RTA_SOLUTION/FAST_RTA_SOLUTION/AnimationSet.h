#pragma once
#include <vector>
#include "Animation.h"
#include "BindPose.h"

class AnimationSet
{
	std::vector<Animation> m_animations;
	const BindPose* m_bindPose;
	std::vector<std::vector<BlendInfo> > m_blendTimes;
	int m_defaultAnim;
public:
	AnimationSet();
	~AnimationSet();
	bool AddAnimation(FILE* _file);
	bool AddBindPose(const BindPose* _pose);
	unsigned int GetAnimationCount() const;
	const Animation* GetAnimation(int _key) const;
	const BlendInfo* GetBlendInfo(int _animationFrom, int _animationTo);
	const BindPose* GetBindPose() const;
	const Animation* GetDefaultAnimation();
};

