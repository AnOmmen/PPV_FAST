


////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Camera.h"

//The class constructor will initialize the position and rotation of the camera to be at the origin of the scene.

Camera::Camera()
{

}


Camera::Camera(XMMATRIX _view)
{
	m_viewMatrix = _view;

	pos = { 0, 3, -15, 0 };
	look = { 0, 0, 0, 0 };
	up = { 0, 1, 0, 0 };
}

Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}

//The SetPosition and SetRotation functions are used for setting up the position and rotation of the camera.

void Camera::SetPosition(float x, float y, float z)
{

	return;
}


void Camera::SetRotation(float x, float y, float z)
{

	return;
}

//The GetPosition and GetRotation functions return the location and rotation of the camera to calling functions.

XMFLOAT3 Camera::GetPosition()
{
	return XMFLOAT3();
}


XMFLOAT3 Camera::GetRotation()
{
	return XMFLOAT3();
}

//The Update function uses the position and rotation of the camera to build and update the view matrix.
//We first setup our variables for up, position, rotation, and so forth.Then at the origin of the scene 
//we first rotate the camera based on the x, y, and z rotation of the camera.Once it is properly rotated 
//when then translate the camera to the position in 3D space.With the correct values in the position,
//lookAt, and up we can then use the XMMatrixLookAtLH function to create the view matrix to represent 
//the current camera rotation and translation.

void Camera::Update(bool* keyarray, float dt)
{
	XMMATRIX identity;
	identity = XMMatrixIdentity();
	if (keyarray[12])
	{
		//positive y rotation
		identity = XMMatrixMultiply(identity, XMMatrixRotationY(-0.5 * dt));
	}
	if (keyarray[13])
	{
		//negative y rotation
		identity = XMMatrixMultiply(identity, XMMatrixRotationY(0.5 * dt));
	}
	if (keyarray[14])
	{
		//negative x rotation
		identity = XMMatrixMultiply(identity, XMMatrixRotationX(-0.5 * dt));
	}
	if (keyarray[15])
	{
		//positive x rotation
		identity = XMMatrixMultiply(identity, XMMatrixRotationX(0.5 * dt));
	}
	if (keyarray[0])
	{
		identity = XMMatrixMultiply(identity, XMMatrixTranslation(0, 0, -1 * dt));
	}
	if (keyarray[1])
	{
		identity = XMMatrixMultiply(identity, XMMatrixTranslation(1 * dt, 0, 0));
	}
	if (keyarray[2])
	{
		identity = XMMatrixMultiply(identity, XMMatrixTranslation(0, 0, 1 * dt));
	}
	if (keyarray[3])
	{
		identity = XMMatrixMultiply(identity, XMMatrixTranslation(-1 * dt, 0, 0));
	}
	if (keyarray[4])
	{
		identity = XMMatrixMultiply(identity, XMMatrixTranslation(0, 1 * dt, 0));

	}
	if (keyarray[5])
	{
		identity = XMMatrixMultiply(identity, XMMatrixTranslation(0, -1 * dt, 0));

	}

	m_viewMatrix = XMMatrixMultiply(m_viewMatrix, identity);

	return;
}

//After Render function has been called to create the view matrix we can provide the updated view matrix to calling functions using this GetViewMatrix function.The view matrix will be one of the three main matrices used in the HLSL vertex shader.

XMMATRIX& Camera::GetViewMatrix()
{

	return m_viewMatrix;
}