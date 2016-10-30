#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Mesh.h"
using namespace DirectX;
class Model
{
private:
	std::vector<Model*> m_children;
	XMMATRIX m_local;
	XMMATRIX m_world;
	Mesh* m_Mesh;
	void Update(XMMATRIX& _matrix);
public:
	struct FullVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT3 norm;
		DirectX::XMFLOAT4 tan;
	};
	Model();
	~Model();
	void Update();
	const XMMATRIX& GetWorldMat();
	unsigned int AddChild(Model& _mod);
	void RemoveChild(unsigned int _index);
	size_t GetChildCount() const;
	//giving compile errors TODO
	Model& GetChild(unsigned int _index) const;
	//Model& const GetChild(unsigned int) const;
};

