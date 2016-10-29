#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
enum ANIM_TYPE
{
	LOOP = 0,
	RETURN_DEFAULT = 1,
	RETURN_LAST = 2,
	RUN_ONCE = 1
};
struct Bone
{
	XMMATRIX m_world;
};
struct KeyFrame
{
	int m_numBones;
	float m_time;
	std::vector<Bone> m_worldVec;
};
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

