#include "Mesh.h"


Mesh::Mesh(ID3D11Device* device)
{


	//TEST CASE TO MAKE A PLANE

}


Mesh::~Mesh()
{

}


unsigned short Mesh::GetNumIndeces()
{
	return indeces.size();
}

ID3D11Buffer** Mesh::GetVertBuff()
{
	return &vertexBuffer;
}
ID3D11Buffer** Mesh::GetIndexBuff()
{
	return &indexBuffer;
}

void Mesh::CreateMesh(ID3D11Device* device, std::vector<Vertex> _vertices, std::vector<unsigned short> _indices)
{
	


	vertices = _vertices;
	indeces = _indices;

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices.data();
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(Vertex) * vertices.size(), D3D11_BIND_VERTEX_BUFFER);
	device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		&vertexBuffer
	);


	D3D11_SUBRESOURCE_DATA cubeindexBufferData = { 0 };
	cubeindexBufferData.pSysMem = indeces.data();
	cubeindexBufferData.SysMemPitch = 0;
	cubeindexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC cubeindexBufferDesc(sizeof(unsigned short) * indeces.size(), D3D11_BIND_INDEX_BUFFER);

	device->CreateBuffer(
		&cubeindexBufferDesc,
		&cubeindexBufferData,
		&indexBuffer
	);
}