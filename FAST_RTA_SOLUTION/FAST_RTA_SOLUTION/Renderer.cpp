#include "Renderer.h"



Renderer::Renderer()
{
	m_polyShader = new PolyShader();
	//make a temp model to test plane
	m_objects.clear();

}


Renderer::~Renderer()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_polyShader->RemoveModel(m_objects[i]);
	}
}

void Renderer::Render(ID3D11DeviceContext* deviceContext, XMMATRIX proj)
{
	//TODO: indexCount??
	//setup temp camera
	XMVECTORF32 pos, look, up;
	pos = { 0, 3, -15, 0 };
	look = { 0, 0, 0, 0 };
	up = { 0, 1, 0, 0 };
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_polyShader->Render(deviceContext, m_objects[i]->GetNumMeshIndeces(), 
			m_objects[i]->GetWorldMat(), XMMatrixLookAtLH(pos, look, up), proj, m_objects[i]);
	}
}


void Renderer::AddModel(ID3D11Device* device, HWND hwnd, Model* key)
{
	m_objects.push_back(key);
	m_polyShader->AddModel(key, vs, ps, NULL, device, hwnd, L"VertexShader.hlsl", L"PixelShader.hlsl", NULL);

}