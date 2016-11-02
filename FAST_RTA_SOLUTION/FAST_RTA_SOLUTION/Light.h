#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
class Light
{
private:
	struct LIGHT
	{
		//w of pos 0 = directional light 1 = point light 2 = spotlight
		XMFLOAT4 pos;
		XMFLOAT4 color;
		XMFLOAT4 normal;
		XMFLOAT4 r;
	};
	LIGHT m_lights[3];
	ID3D11Buffer* m_LightBuffer;
public:
	Light();
	Light(ID3D11Device* device);
	void Update(bool*keys, float dt);
	~Light();
	void AddDirLight(XMFLOAT4& _pos, XMFLOAT4& _color, XMFLOAT4& _normal, XMFLOAT4& _r, ID3D11DeviceContext* context);
	void AddSpotLight(XMFLOAT4& _pos, XMFLOAT4& _color, XMFLOAT4& _normal, XMFLOAT4& _r, ID3D11DeviceContext* context);
	void AddPointLight(XMFLOAT4& _pos, XMFLOAT4& _color, XMFLOAT4& _normal, XMFLOAT4& _r, ID3D11DeviceContext* context);
	void UpdateBuffer(ID3D11DeviceContext* context);
};

