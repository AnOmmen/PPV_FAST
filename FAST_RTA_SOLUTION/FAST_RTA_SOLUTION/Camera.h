
#pragma once

////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Camera_H_
#define _Camera_H_


//////////////
// INCLUDES //

//////////////
#include <directxmath.h>
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: Camera
////////////////////////////////////////////////////////////////////////////////
class Camera
{
public:
	Camera(XMMATRIX _view);
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT4 GetPosition();
	XMFLOAT3 GetRotation();

	void Update(bool* keyarray, float dt);
	XMMATRIX& GetViewMatrix();


private:
	Camera();
	/*float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;*/
	XMFLOAT4 pos, look, up;
	XMMATRIX m_viewMatrix;
};

#endif