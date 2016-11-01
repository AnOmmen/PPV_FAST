#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	m_deviceResources = new DeviceResources();
	m_renderer = new Renderer();
	
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
	Model* model = new Model(m_deviceResources->GetDevice());
	m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
}


void ResourceManager::Update()
{

}

void ResourceManager::Render()
{
	m_deviceResources->GetProjectionMatrix(m_proj);
	m_deviceResources->BeginScene(.5, .5, .5, 1);
	m_renderer->Render(m_deviceResources->GetDeviceContext(), m_proj);
	m_deviceResources->EndScene();
}