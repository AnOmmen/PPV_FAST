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
	std::vector<LIGHT> m_lights;
	ID3D11Buffer* m_LightBuffer;
public:
	Light();
	Light(XMFLOAT4& _a, XMFLOAT4& _b, XMFLOAT4& _c);
	~Light();
	void SetSpacial(XMFLOAT4& _vec);
	void SetColor(XMFLOAT4& _vec);
	void SetIdentity(XMFLOAT4& _vec);
	XMFLOAT4 const & GetSpacial() const;
	XMFLOAT4 const & GetColor() const;
	XMFLOAT4 const & GetIdentity() const;
};

