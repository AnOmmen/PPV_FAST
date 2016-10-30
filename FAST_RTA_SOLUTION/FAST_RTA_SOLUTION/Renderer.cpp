#include "Renderer.h"

void CreateLights(Light* lights, ID3D11DeviceContext* context)
{
	XMFLOAT4 temp1 = XMFLOAT4(0, 5, 0, 1.0f);
	XMFLOAT4 temp2 = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 temp3 = XMFLOAT4(0.0f, -1.0f, 0.0f, 1.0f);
	XMFLOAT4 temp4 = XMFLOAT4(200.0f, 0.99f, 0.8f, 0.0f);


	lights->AddSpotLight(temp1,temp2 ,temp3
		,temp4 , context);

}

Renderer::Renderer(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_polyShader = new PolyShader();
	//make a temp model to test plane
	m_objects.clear();
	m_light = new Light(device);

	//create light
	CreateLights(m_light, context);
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
	XMMATRIX view = (XMMatrixLookAtLH(pos, look, up));
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_light->UpdateBuffer(deviceContext);
		m_polyShader->Render(deviceContext, m_objects[i]->GetNumMeshIndeces(), 
			(m_objects[i]->GetWorldMat()), view, proj, m_objects[i]);
	}
}


void Renderer::AddModel(ID3D11Device* device, HWND hwnd, Model* key)
{
	m_objects.push_back(key);
	m_polyShader->AddModel(key, vs, ps, NULL, device, hwnd, L"VertexShader.hlsl", L"PixelShader.hlsl", NULL);

}