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
	unsigned long GetNumBones() const;
	// THIS COPIES DATA, IT DOES NOT POINT TO THE CONSTANT DATA //
	void init(unsigned long _num, const DirectX::XMFLOAT4X4* _mat);
};

