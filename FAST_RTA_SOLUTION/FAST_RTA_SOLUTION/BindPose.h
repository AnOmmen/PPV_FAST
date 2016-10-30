#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
class BindPose
{
public:
	XMMATRIX m_invBindPose;
	int num_bones;
	BindPose();
	~BindPose();
	const XMMATRIX* GetBindPose();
	int GetNumBones();
	void init(int _num, XMMATRIX* _mat);
};

