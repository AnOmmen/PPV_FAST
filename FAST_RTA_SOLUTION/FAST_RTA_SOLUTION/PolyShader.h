#pragma once
#include "Model.h"
using namespace DirectX;
class PolyShader
{
private:
	std::vector<Model*> m_models;
	ID3D11VertexShader* m_vs;
	ID3D11PixelShader* m_ps;
	ID3D11GeometryShader* m_gs;
public:
	PolyShader();
	~PolyShader();
	void AddModel(Model&);
	void RemoveModel(Model&);
	unsigned int GetModelCount() const;
	Model& const GetModel(unsigned int) const;
	void SetVS(ID3D11VertexShader* _vs);
	void SetPS(ID3D11PixelShader* _ps);
	void SetGS(ID3D11GeometryShader* _gs);
	ID3D11VertexShader const* GetVS() const;
	ID3D11PixelShader const* GetPS() const;
	ID3D11GeometryShader const* GetGS() const;
};

