#pragma once
#include "Renderer.h"
#include "DeviceResources.h"
#include "Blender.h"
class ResourceManager
{
private:
	DeviceResources* m_deviceResources;
	Renderer* m_renderer;
	XMMATRIX m_proj;
	ID3D11SamplerState* SampState;
	ID3D11Texture2D* texture;
	Blender* blender;
	float currentTime;
	int currentFrame;
	bool pressed;
	bool loop;
public:
	void Init(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
		float screenDepth, float screenNear);
	void Update(bool* keys, float dt, HWND hwnd);
	void Render();
	ResourceManager();
	void loadOBJ(char* filename, wchar_t* texturename, ID3D11Device* device,
		std::vector<FullVertex> &_vertices, std::vector<unsigned short> &_indeces);


	~ResourceManager();
};

