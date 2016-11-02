#pragma once
#include <vector>
#include <DirectXMath.h>

enum ANIM_TYPE
{
	LOOP = 0,
	RETURN_DEFAULT = 1,
	RETURN_LAST = 2,
	RUN_ONCE = 1
};

struct Bone
{
	DirectX::XMMATRIX m_world;
};

struct Skeleton
{
	std::vector<Bone> sk;
};

struct KeyFrame
{
	float m_time;
	Skeleton m_skeleton;
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

struct FullVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 norm;
	DirectX::XMFLOAT3 tan;
	DirectX::XMFLOAT4 bWeights;
	DirectX::XMFLOAT4 bIndices;
};
