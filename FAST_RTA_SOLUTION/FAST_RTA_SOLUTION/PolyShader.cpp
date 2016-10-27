#include "PolyShader.h"



PolyShader::PolyShader()
{
}


PolyShader::~PolyShader()
{
}

void PolyShader::AddModel(Model &)
{
}

void PolyShader::RemoveModel(Model &)
{
}

unsigned int PolyShader::GetModelCount() const
{
	return 0;
}

Model & const PolyShader::GetModel(unsigned int) const
{
	Model* placeHolder;
	return *placeHolder;
}

void PolyShader::SetVS(ID3D11VertexShader * _vs)
{
}

void PolyShader::SetPS(ID3D11PixelShader * _ps)
{
}

void PolyShader::SetGS(ID3D11GeometryShader * _gs)
{
}

ID3D11VertexShader const * PolyShader::GetVS() const
{
	return nullptr;
}

ID3D11PixelShader const * PolyShader::GetPS() const
{
	return nullptr;
}

ID3D11GeometryShader const * PolyShader::GetGS() const
{
	return nullptr;
}
