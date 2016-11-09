#pragma once
#include "Interpolator.h"
#include "AnimationSet.h"
class Blender
{
public:
	AnimationSet* m_animationContainer;
	BlendInfo* m_blend;
	std::vector<DirectX::XMMATRIX> m_boneOffsetArray;
	Interpolator* m_currAnim;
	Interpolator* m_nextAnim;
	KeyFrame m_updatedKeyFrame;
	Blender(const Animation* anim);
	~Blender();
	KeyFrame GetUpdatedKeyFrame() const;
	const DirectX::XMMATRIX* GetSkinningMatrix();
	void SetAnimSet(std::string _key);
	bool SetNextAnim(BLEND_TYPE _type, int _animKey);
	void Update(float _time);
};

