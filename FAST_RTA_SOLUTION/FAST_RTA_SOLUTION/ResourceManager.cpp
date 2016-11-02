#include "ResourceManager.h"
#include "DDSTextureLoader.h"
#include "../FAST_FBX_LOADER/FASTFBXLoader.h"

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

	{
		FASTFBXLoader::Init();
		FASTFBXLoader::Load("../FAST_RTA_SOLUTION/Box_Idle.fbx", NULL);
		Model* model;
		std::vector<FullVertex> vertices;
		std::vector<unsigned short>* pindeces;
		std::vector<unsigned short> indeces;

		unsigned int vertexCount;
		vertexCount = FASTFBXLoader::GetVertexCount();
		pindeces = &(FASTFBXLoader::GetIndices());
		for (size_t i = 0; i < pindeces->size(); i++)
		{
			indeces.push_back(pindeces->at(i));
		}


		vertices.resize(vertexCount);
		void * verts = FASTFBXLoader::GetVertices();
		for (size_t i = 0; i < vertexCount; i++)
		{
			memcpy_s(&vertices[i], vertexCount * sizeof(FullVertex), verts, vertexCount * sizeof(FullVertex));
		}

		std::vector<Vertex> rverts;
	
		float* vertArray = (float*)verts;
		for (size_t i = 0; i < vertexCount; i++)
		{
			Vertex temp;
			temp.pos = XMFLOAT4(vertArray[(i * sizeof(FullVertex))], vertArray[(i * sizeof(FullVertex)) + 1], vertArray[(i * sizeof(FullVertex)) + 2], 1.0f);
			temp.color = XMFLOAT4(1.0, 1.0, 1.0, 1.0);
			temp.norm = XMFLOAT4(vertArray[(i * sizeof(FullVertex)) + 5], vertArray[(i * sizeof(FullVertex)) + 6], vertArray[(i * sizeof(FullVertex)) + 7], 1.0f);
			rverts.push_back(temp);
		}




		model = new Model(m_deviceResources->GetDevice(), rverts, indeces);








		FASTFBXLoader::Clean();
	}
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indeces;
	m_renderer = new Renderer(m_deviceResources->GetDevice(), m_deviceResources->GetDeviceContext());
	Model* model;
	//
	//char* myFilename = "Cube.obj";
	//wchar_t*temp = L"cubeskybox.dds";
	//
	//loadOBJ(myFilename, temp, m_deviceResources->GetDevice(), XMFLOAT3(), vertices, indeces);
	//
	//Model* model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	//HRESULT hr;
	//if (temp != NULL)
	//{
	//	hr = CreateDDSTextureFromFile(m_deviceResources->GetDevice(),
	//		temp, NULL,
	//		&model->shaderview);
	//}
	//
	//
	//
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//
	Vertex topright, topleft, bottomright, bottomleft;
	topright.pos = XMFLOAT4(10, 0, 10, 1);
	topleft.pos = XMFLOAT4(-10, 0, 10, 1);
	bottomright.pos = XMFLOAT4(10, 0, -10, 1);
	bottomleft.pos = XMFLOAT4(-10, 0, -10, 1);
	
	topright.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	topleft.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	bottomright.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	bottomleft.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	
	topright.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	topleft.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bottomright.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bottomleft.norm = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	vertices.clear();
	vertices.push_back(topleft);
	vertices.push_back(topright);
	vertices.push_back(bottomleft);
	vertices.push_back(bottomright);
	
	//1, 2, 4
	
	indeces.clear();
	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);
	
	//2, 4, 3
	indeces.push_back(1);
	indeces.push_back(3);
	indeces.push_back(2);
	
	
	
	
	model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//std::vector<unsigned short> backward;
	//backward.resize(indeces.size());
	//for (int i = 0; i < indeces.size(); i++)
	//{
	//	backward[i] = indeces[indeces.size() - 1 - i];
	//}
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, -1, 0, 1);
	//}
	//
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, backward);
	//
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//
	//
	//
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, 1, 0, 1);
	//}
	//
	//
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	//XMMATRIX trans = XMMatrixTranslation(0, 3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, -1, 0, 1);
	//}
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, backward);
	//trans = XMMatrixTranslation(0, 3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, 1, 0, 1);
	//}
	//
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	//trans = XMMatrixTranslation(0, -3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, -1, 0, 1);
	//}
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, backward);
	//trans = XMMatrixTranslation(0, -3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	////cube code
	//Vertex T1, T2, T3, T4, B1, B2, B3, B4;
	//float left, right, up, down, top, bottom;
	//left = down = bottom = -2;
	//up = right = top = 2;
	//T1.pos = XMFLOAT4(left, bottom, up, 1.0f);
	//T2.pos = XMFLOAT4(right, bottom, up, 1.0f);
	//T3.pos = XMFLOAT4(left, bottom, down, 1.0f);
	//T4.pos = XMFLOAT4(right, bottom, down, 1.0f);
	//B1.pos = XMFLOAT4(left, bottom, up, 1.0f);
	//B2.pos = XMFLOAT4(right, bottom, up, 1.0f);
	//B3.pos = XMFLOAT4(left, bottom, down, 1.0f);
	//B4.pos = XMFLOAT4(right, bottom, down, 1.0f);




}

void ResourceManager::loadOBJ(char* filename, wchar_t* texturename, ID3D11Device* device, XMFLOAT3 offset,
	std::vector<Vertex> &_vertices, std::vector<unsigned short> &_indeces)
{
	if (filename)
	{
		std::vector<Vertex> Iverts;
		std::vector<unsigned int> Iindeces;
		std::vector<XMFLOAT3> verts, normals;
		std::vector<XMFLOAT2> uvs;
		std::vector<unsigned int> vi, uvi, ni;
		FILE* file;
		fopen_s(&file, filename, "r");
		if (file != NULL)
		{

			int i = 0;
			while (true)
			{

				char header[128];
				int res = fscanf_s(file, "%s", header, 128);
				if (res == EOF)
				{
					break;
				}
				if (strcmp(header, "v") == 0)
				{
					XMFLOAT3 vert;
					fscanf_s(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
					vert.x;
					vert.y;
					vert.z;
					verts.push_back((vert));
				}
				else if (strcmp(header, "vt") == 0)
				{
					XMFLOAT2 uv;
					fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
					uv.y = 1 - uv.y;
					uvs.push_back(uv);
				}
				else if (strcmp(header, "vn") == 0)
				{
					XMFLOAT3 norm;
					fscanf_s(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
					normals.push_back(norm);
				}
				else if (strcmp(header, "f") == 0)
				{

					unsigned int indeces[9];
					int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
						&indeces[0], &indeces[1], &indeces[2], &indeces[3],
						&indeces[4], &indeces[5], &indeces[6], &indeces[7],
						&indeces[8]);

					vi.push_back(indeces[0] - 1);
					vi.push_back(indeces[6] - 1);
					vi.push_back(indeces[3] - 1);

					uvi.push_back(indeces[1] - 1);
					uvi.push_back(indeces[7] - 1);
					uvi.push_back(indeces[4] - 1);

					ni.push_back(indeces[2] - 1);
					ni.push_back(indeces[8] - 1);
					ni.push_back(indeces[5] - 1);


				}
				else
				{
					continue;
				}

			}

		}


		std::vector<Vertex> vertices;
		std::vector<unsigned short> indeces;

		for (size_t i = 0; i < vi.size(); i++)
		{
			Vertex temp;
			temp.pos = XMFLOAT4(verts[vi[i]].x, verts[vi[i]].y, verts[vi[i]].z, 1.0f);
			temp.color = XMFLOAT4(1.0, 1.0, 1.0, 1.0);
			temp.norm = XMFLOAT4(verts[vi[i]].x, verts[vi[i]].y, verts[vi[i]].z, 1.0f);
			Iverts.push_back(temp);
			Iindeces.push_back(i);
		}
		_vertices = Iverts;
		_indeces.clear();
		for (int i = 0; i < Iindeces.size(); i++)
		{
			_indeces.push_back(Iindeces[i]);
		}




	}
}

void ResourceManager::Update(bool* keys, float dt)
{
	m_renderer->Update(keys, dt);
}

void ResourceManager::Render()
{
	m_deviceResources->GetProjectionMatrix(m_proj);
	m_deviceResources->BeginScene(.5, .5, .5, 1);
	m_renderer->Render(m_deviceResources->GetDeviceContext(), m_proj);
	m_deviceResources->EndScene();
}
