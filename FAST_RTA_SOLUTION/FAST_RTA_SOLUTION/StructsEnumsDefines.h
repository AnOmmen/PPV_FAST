#pragma once
#include <vector>
#include <DirectXMath.h>

enum ANIM_TYPE
{
	INIT_ERROR = -1,
	LOOP,
	RETURN_DEFAULT,
	RETURN_LAST,
	RUN_ONCE
};

struct Bone
{
	DirectX::XMFLOAT4X4 m_world;
};

struct KeyFrame
{
	float m_time;
	std::vector<Bone> m_bones;
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
