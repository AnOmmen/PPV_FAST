#pragma once
#include <vector>
#include "Animation.h"
#include "BindPose.h"
enum BLEND_TYPE
{
	CUR_GO_NEXT_GO,
	CUR_GO_NEXT_STOP,
	CUR_STOP_NEXT_GO,
	CUR_STOP_NEXT_STOP,
	DEFAULT, 
	POP_NEXT
};
struct BlendInfo
{
	BLEND_TYPE m_blendStyle;
	float m_totalBlendTime;
};
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

