#pragma once
#include <vector>
#include "Animation.h"

class BindPose;

class AnimationSet
{
	std::vector<Animation> m_animations;
	BindPose* m_bindPose;
	std::vector<std::vector<BlendInfo> > m_blendTimes;
	unsigned long m_defaultAnim;
public:
	AnimationSet();
	~AnimationSet();
	// On the first call of this function, it will attempt to set _indices and _vertices to their
	// respective data, however if on the first call any pointers passed in are set to nullptr
	// the function will not complete loading the animation file and will return false
	// On subsequent calls after the first, the function will only load animation data into its
	// list of animations as it will have already delievered the redundent mesh data and bindpose
	// data which should be the same if the file being loaded is associated to the correct mesh
	bool LoadAnimationFile(const char *_filePath, unsigned short **_indices = nullptr, unsigned long *_indexCount = nullptr,
		FullVertex **_vertices = nullptr, unsigned long *_vertexCount = nullptr);
	unsigned int GetAnimationCount() const;
	const Animation* GetAnimation(int _key) const;
	const BlendInfo* GetBlendInfo(int _animationFrom, int _animationTo) const;
	BindPose* GetBindPose() const;
	const Animation* GetDefaultAnimation() const;
	void SetBlendTimes(std::vector<std::vector<BlendInfo>> &_blendTimes);
	void SetBlendTime(int _animationFrom, int _animationTo, BlendInfo &_blendInfo);
	void SetDefaultAnimation(unsigned long _defaultAnim);
};

