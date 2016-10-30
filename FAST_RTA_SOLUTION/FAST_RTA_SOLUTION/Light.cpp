#include "Light.h"

#define DIRECTIONAL_LIGHT -1
#define POINT_LIGHT -2

Light::Light()
{

}

Light::Light(XMFLOAT4 & _spacial, XMFLOAT4 & _color, XMFLOAT4 & _identity)
{

}


Light::~Light()
{
}

void Light::SetSpacial(XMFLOAT4 & _vec)
{

}

void Light::SetColor(XMFLOAT4 & _vec)
{

}

void Light::SetIdentity(XMFLOAT4 & _vec)
{
	
}

XMFLOAT4 const & Light::GetSpacial() const
{
	// TODO: insert return statement here
	return XMFLOAT4();
}

XMFLOAT4 const & Light::GetColor() const
{
	// TODO: insert return statement here
	return XMFLOAT4();

}

XMFLOAT4 const & Light::GetIdentity() const
{
	// TODO: insert return statement here
	return XMFLOAT4();

}
