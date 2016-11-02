#pragma once
#include <vector>
#include <DirectXMath.h>

class BindPose
{
	std::vector<DirectX::XMFLOAT4X4> bindposeInverses;
public:
	BindPose();
	~BindPose();
	const DirectX::XMFLOAT4X4* GetBindPose() const;
	int GetNumBones() const;
	void init(int _num, const DirectX::XMFLOAT4X4* _mat);
};

