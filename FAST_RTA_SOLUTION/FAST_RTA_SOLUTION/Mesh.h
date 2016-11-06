#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "StructsEnumsDefines.h"
using namespace DirectX;
struct Vertex
{
	XMFLOAT4 pos;
	XMFLOAT4 color;
	XMFLOAT4 norm;
};

class Mesh
{
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	std::vector<FullVertex> vertices;
	std::vector<unsigned short> indeces;
	Mesh();
public:
	Mesh(ID3D11Device* device);
	~Mesh();
	unsigned short GetNumIndeces();
	ID3D11Buffer** GetVertBuff();
	ID3D11Buffer** GetIndexBuff();
	void CreateMesh(ID3D11Device* device, std::vector < FullVertex > _vertices, std::vector<unsigned short> _indices);
	unsigned short* GetIndeces();
	FullVertex* GetVertices();
	unsigned int GetNumVerts();
};

