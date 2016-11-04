#pragma once
#include <vector>
#include "Animation.h"

class BindPose;

class AnimationSet
{
	std::vector<Animation> m_animations;
	BindPose* m_bindPose;
	std::vector<std::vector<BlendInfo> > m_blendTimes;
	int m_defaultAnim;
public:
	AnimationSet();
	~AnimationSet();
	bool LoadAnimationFile(const char *_filePath, unsigned short *_indices, unsigned long &_indexCount,
		FullVertex *_vertices, unsigned long &_vertexCount);
	unsigned int GetAnimationCount() const;
	const Animation* GetAnimation(int _key) const;
	const BlendInfo* GetBlendInfo(int _animationFrom, int _animationTo);
	const BindPose* GetBindPose() const;
	const Animation* GetDefaultAnimation();
};

