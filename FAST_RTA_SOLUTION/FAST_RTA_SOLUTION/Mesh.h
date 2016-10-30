#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
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
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indeces;
	Mesh();
public:
	Mesh(ID3D11Device* device);
	~Mesh();
	unsigned short GetNumIndeces();
	ID3D11Buffer** GetVertBuff();
	ID3D11Buffer** GetIndexBuff();
};

