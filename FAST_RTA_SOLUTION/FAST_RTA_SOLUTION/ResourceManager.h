#pragma once
#include "Renderer.h"
#include "DeviceResources.h"
class ResourceManager
{
private:
	DeviceResources* m_deviceResources;
	Renderer* m_renderer;
	XMMATRIX m_proj;
public:
	void Init(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
		float screenDepth, float screenNear);
	void Update(bool* keys, float dt);
	void Render();
	ResourceManager();
	~ResourceManager();
};

