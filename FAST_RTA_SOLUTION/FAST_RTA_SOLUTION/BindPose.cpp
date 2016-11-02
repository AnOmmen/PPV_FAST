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

int BindPose::GetNumBones() const
{
	return bindposeInverses.size();
}

void BindPose::init(int _num, const DirectX::XMFLOAT4X4 * _mat)
{
	bindposeInverses.clear();
	bindposeInverses.resize(_num);
	memcpy_s(&bindposeInverses[0], bindposeInverses.size(), _mat, _num);
}