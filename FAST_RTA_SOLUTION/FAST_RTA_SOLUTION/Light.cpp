#include "Light.h"

#define DIRECTIONAL_LIGHT -1
#define POINT_LIGHT -2

Light::Light()
{
	m_spacial = { 0, 0, 0, 0 };
	m_color = { 0, 0, 0, 0 };
	m_identity = { 0, 0, 0, 0 };
}

Light::Light(XMFLOAT4 & _spacial, XMFLOAT4 & _color, XMFLOAT4 & _identity)
{
	m_spacial = _spacial;
	m_color = _color;
	m_identity = _identity;
}


Light::~Light()
{
}

void Light::SetSpacial(XMFLOAT4 & _vec)
{
	m_spacial = _vec;
}

void Light::SetColor(XMFLOAT4 & _vec)
{
	m_color = _vec;
}

void Light::SetIdentity(XMFLOAT4 & _vec)
{
	m_identity = _vec;
}

XMFLOAT4 const & Light::GetSpacial() const
{
	// TODO: insert return statement here
	return m_spacial;
}

XMFLOAT4 const & Light::GetColor() const
{
	// TODO: insert return statement here
	return m_color;
}

XMFLOAT4 const & Light::GetIdentity() const
{
	// TODO: insert return statement here
	return m_identity;
}
