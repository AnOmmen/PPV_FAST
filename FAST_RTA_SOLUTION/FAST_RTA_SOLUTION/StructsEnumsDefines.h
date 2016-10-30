#pragma once
#include <d3d11.h>
#include <vector>
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
