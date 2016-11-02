#pragma once
#pragma comment(lib, "d3d11.lib")
#include "Model.h"
#include "Light.h"
#include "PolyShader.h"
#include "Camera.h"
class Renderer
{
private:
	std::vector<Model*> m_objects;
	Light* m_light;
	PolyShader* m_polyShader;
	//temp shaders
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	Camera* m_camera;
	Renderer();
public:
	Renderer(ID3D11Device* device, ID3D11DeviceContext* context);
	~Renderer();

	void Update(bool* keys, float dt);
	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX proj);
	void AddModel(ID3D11Device* device, HWND hwnd, Model* key);
};

