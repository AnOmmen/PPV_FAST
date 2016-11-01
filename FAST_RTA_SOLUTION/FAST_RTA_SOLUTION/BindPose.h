#pragma once
#include <vector>
#include <DirectXMath.h>

class BindPose
{
public:
	std::vector<DirectX::XMMATRIX> bindposeInverses;
	BindPose();
	~BindPose();
	const DirectX::XMMATRIX* GetBindPose();
	int GetNumBones();
	void init(int _num, DirectX::XMMATRIX* _mat);
};

