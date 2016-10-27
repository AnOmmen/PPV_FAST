#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
class Light
{
private:
	XMFLOAT4 m_spacial;
	XMFLOAT4 m_color;
	XMFLOAT4 m_identity;
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

