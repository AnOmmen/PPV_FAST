#include "Light.h"

#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
Light::Light()
{

}
Light::Light(ID3D11Device* device)
{
	CD3D11_BUFFER_DESC constlightbufferdesc(sizeof(LIGHT) * 3, D3D11_BIND_CONSTANT_BUFFER);
	
		device->CreateBuffer(
			&constlightbufferdesc,
			nullptr,
			&m_LightBuffer);
		ZeroMemory(m_lights, sizeof(LIGHT) * 3);
}




Light::~Light()
{
	m_LightBuffer->Release();
}

void Light::AddDirLight(XMFLOAT4& _pos, XMFLOAT4& _color, XMFLOAT4& _normal, XMFLOAT4& _r, ID3D11DeviceContext* context)
{
	
	m_lights[DIRECTIONAL_LIGHT].pos = _pos;
	m_lights[DIRECTIONAL_LIGHT].color = _color;
	m_lights[DIRECTIONAL_LIGHT].normal = _normal;
	m_lights[DIRECTIONAL_LIGHT].r = _r;
	UpdateBuffer(context);

}
void Light::AddSpotLight(XMFLOAT4& _pos, XMFLOAT4& _color, XMFLOAT4& _normal, XMFLOAT4& _r, ID3D11DeviceContext* context)
{
	m_lights[SPOT_LIGHT].pos = _pos;
	m_lights[SPOT_LIGHT].color = _color;
	m_lights[SPOT_LIGHT].normal = _normal;
	m_lights[SPOT_LIGHT].r = _r;
	UpdateBuffer(context);


}
void Light::AddPointLight(XMFLOAT4& _pos, XMFLOAT4& _color, XMFLOAT4& _normal, XMFLOAT4& _r, ID3D11DeviceContext* context)
{
	m_lights[POINT_LIGHT].pos = _pos;
	m_lights[POINT_LIGHT].color = _color;
	m_lights[POINT_LIGHT].normal = _normal;
	m_lights[POINT_LIGHT].r = _r;
	UpdateBuffer(context);


}


void Light::UpdateBuffer(ID3D11DeviceContext* context)
{
	context->UpdateSubresource(
		m_LightBuffer,
		0,
		NULL,
		&m_lights,
		0,
		0
	);
	context->PSSetConstantBuffers(
		0,
		1,
		&m_LightBuffer);

}
