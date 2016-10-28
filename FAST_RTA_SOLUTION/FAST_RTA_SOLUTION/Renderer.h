#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
using namespace DirectX;
#include <vector>
#include "Model.h"
#include "Light.h"
#include "PolyShader.h"
class Renderer
{
private:
	std::vector<Model> m_objects;
	//constant buffers
	std::vector<Light> m_lights;
	PolyShader* m_polyShader;
public:
	Renderer();
	~Renderer();
};

