#include "Mesh.h"



Mesh::Mesh(ID3D11Device* device)
{
	//TEST CASE TO MAKE A PLANE
	Vertex topright, topleft, bottomright, bottomleft;
	topright.pos = XMFLOAT4(10, 0, 10, 1);
	topleft.pos = XMFLOAT4(-10, 0, 10, 1);
	bottomright.pos = XMFLOAT4(10, 0, -10, 1);
	bottomleft.pos = XMFLOAT4(-10, 0, -10, 1);

	topright.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	topleft.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	bottomright.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	bottomleft.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	topright.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	topleft.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bottomright.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bottomleft.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	
	vertices.push_back(topleft);
	vertices.push_back(topright);
	vertices.push_back(bottomleft);
	vertices.push_back(bottomright);

	//1, 2, 4
	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);

	//2, 4, 3
	indeces.push_back(1);
	indeces.push_back(3);
	indeces.push_back(2);

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