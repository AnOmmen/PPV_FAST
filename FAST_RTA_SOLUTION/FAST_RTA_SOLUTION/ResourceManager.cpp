#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	m_deviceResources = new DeviceResources();
}


ResourceManager::~ResourceManager()
{
	m_deviceResources->Shutdown();
	delete m_deviceResources;
}


void ResourceManager::Init(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
	float screenDepth, float screenNear)
{
	m_deviceResources->Initialize(screenWidth, screenHeight, vsync, hwnd, fullscreen, screenDepth, screenNear);
}


void ResourceManager::Update()
{

}
void ResourceManager::Render()
{
	m_deviceResources->BeginScene(.5, .5, .5, 1);
	m_deviceResources->EndScene();
}