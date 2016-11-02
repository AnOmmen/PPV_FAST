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
	void loadOBJ(char* filename, wchar_t* texturename, ID3D11Device* device, XMFLOAT3 offset,
		std::vector<Vertex> &_vertices, std::vector<unsigned short> &_indeces);


	~ResourceManager();
};

