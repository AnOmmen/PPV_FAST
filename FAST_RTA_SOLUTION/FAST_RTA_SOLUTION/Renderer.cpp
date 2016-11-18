#include "Renderer.h"
#include "Blender.h"
extern char *binFilePath;
extern bool loadBinFile;
void CreateLights(Light* lights, ID3D11DeviceContext* context)
{
	XMFLOAT4 temp1 = XMFLOAT4(0, 1, 0, 1.0f);
	XMFLOAT4 temp2 = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 temp3 = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	XMFLOAT4 temp4 = XMFLOAT4(500.0f, 0.0f, 0.0f, 0.0f);


	lights->AddPointLight(temp1,temp2 ,temp3
		,temp4 , context);

	
}

Renderer::Renderer(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_polyShader = new PolyShader();
	//make a temp model to test plane
	m_objects.clear();
	XMVECTORF32 pos, look, up;
	pos = { 0, 3, -15, 0 };
	look = { 0, 0, 0, 0 };
	up = { 0, 1, 0, 0 };
	XMMATRIX view = (XMMatrixLookAtLH(pos, look, up));
	m_camera = new Camera(view);
	m_light = new Light(device);
	//create light
	CreateLights(m_light, context);
	m_device = device;
	m_dragDrop = nullptr;
	m_dragDropBlend = nullptr;
}


Renderer::~Renderer()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_polyShader->RemoveModel(m_objects[i]);
		delete m_objects[i];
	}
	delete m_polyShader;
	delete m_light;
	delete m_camera;

	delete m_dragDrop;
	delete m_dragDropBlend;
}

void Renderer::Render(ID3D11DeviceContext* deviceContext, XMMATRIX proj, Blender* blender)
{
	//TODO: indexCount??
	//setup temp camera
	m_light->UpdateBuffer(deviceContext, m_camera->GetPosition());
	for (int i = 0; i < m_objects.size(); i++)
	{
	
		std::vector<XMMATRIX> temp;
	
		
		for (int j = 0; j < m_objects[i]->timesToDraw; j++)
		{
			temp.push_back(XMMatrixTranslation(100.0f * (float)j, 0.0f, 0.0f) * (m_objects[i]->GetWorldMat()));
		}
		m_polyShader->Render(deviceContext, m_objects[i]->GetNumIndeces(), 
			temp, m_camera->GetViewMatrix(), proj, m_objects[i], blender);
	}
	if (m_dragDrop)
	{
		std::vector<XMMATRIX> temp;
		temp.push_back(m_dragDrop->GetWorldMat());
		m_polyShader->Render(deviceContext, m_dragDrop->GetNumIndeces(), temp,
			m_camera->GetViewMatrix(), proj, m_dragDrop, m_dragDropBlend);
	}
}


void Renderer::AddModel(ID3D11Device* device, HWND hwnd, Model* key)
{
	m_objects.push_back(key);
	
	m_polyShader->AddModel(key, vs, ps, NULL, device, hwnd, L"SkinningShader.hlsl", L"PixelShader.hlsl", NULL);
	
}

void Renderer::Update(bool* keys, float dt, Blender* blender, HWND hwnd)
{
	if (loadBinFile)
	{
		delete m_dragDrop;
		std::vector<FullVertex> vertices;
		std::vector<unsigned short> indices;
		m_dragDrop = new Model(m_device, vertices, indices);
		m_dragDrop->Update(XMMatrixTranslation(-3, 0, 0));
		m_dragDrop->hasAnimation = true;
		m_dragDrop->timesToDraw = 1;
		m_dragDrop->LoadAnimation(binFilePath, m_device);
		m_polyShader->AddModel(m_dragDrop, vs, ps, nullptr, m_device, hwnd, L"SkinningShader.hlsl", L"PixelShader.hlsl", NULL);

		delete m_dragDropBlend;
		m_dragDropBlend = new Blender(m_dragDrop->GetAnimationSet().GetDefaultAnimation());
		m_dragDropBlend->SetAnimSet(&m_dragDrop->GetAnimationSet());

		loadBinFile = false;
	}
	m_light->Update(keys, dt);
	m_camera->Update(keys, dt);
	if (keys[16])
	{
		
		if (blender->m_currAnim->m_animation == m_objects[1]->GetAnimationSet().GetAnimation(0))
		{
			blender->SetNextAnim(m_objects[1]->GetAnimationSet().GetAnimation(1));
		}
		else if (blender->m_currAnim->m_animation == m_objects[1]->GetAnimationSet().GetAnimation(1))
		{
			blender->SetNextAnim(m_objects[1]->GetAnimationSet().GetDefaultAnimation());
		}
	}
	
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->Update(dt);
		if (i >= 2)
			m_objects[i]->Update(XMMatrixMultiply(XMLoadFloat4x4(&blender->m_currAnim->m_currFrame.m_bones[i - 2].m_world), XMMatrixScaling(.01f, .01f, .01f)));
	}
	if (m_dragDrop)
	{
		m_dragDrop->Update(dt);
		m_dragDropBlend->Update(dt);
	}
}