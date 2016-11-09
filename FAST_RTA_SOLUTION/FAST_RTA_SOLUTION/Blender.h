#pragma once
#include "Interpolator.h"
#include "AnimationSet.h"
using namespace DirectX;
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
	 DirectX::XMMATRIX* GetSkinningMatrix();
	void SetAnimSet(AnimationSet*);
	bool SetNextAnim(BLEND_TYPE _type, int _animKey);
	void Update(float _time);
};

