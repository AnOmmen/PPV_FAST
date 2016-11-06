#include "BindPose.h"



BindPose::BindPose()
{
}


BindPose::~BindPose()
{
}

const DirectX::XMFLOAT4X4 * BindPose::GetBindPose() const
{
	return &bindposeInverses[0];
}

unsigned long BindPose::GetNumBones() const
{
	return bindposeInverses.size();
}

void BindPose::init(unsigned long _num, const DirectX::XMFLOAT4X4 * _mat)
{
	bindposeInverses.clear();
	bindposeInverses.resize(_num);
	memcpy_s(&bindposeInverses[0], bindposeInverses.size() * sizeof(DirectX::XMFLOAT4X4), _mat, _num * sizeof(DirectX::XMFLOAT4X4));
}