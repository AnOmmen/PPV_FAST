#pragma once
#include "Animation.h"
class Interpolator
{
public:
	//Members
	const Animation* m_animation;
	float m_currBlendTime;
	KeyFrame m_currFrame;
	float m_totalBlendTime;
	std::vector<Bone> m_world;

	//Methods
	Interpolator();
	~Interpolator();
	Bone* GetCurrentWorld(int &_num);
	float GetTime();
	void SetAnimation(const Animation* _anim);
	void SetTime(float _time);
	ANIM_TYPE Update(float _time);
};
