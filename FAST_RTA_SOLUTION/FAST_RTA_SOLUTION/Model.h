#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
class Model
{
private:
	std::vector<Model*> m_children;
	XMMATRIX m_local;
	XMMATRIX m_world;
	void Update(XMMATRIX& _matrix);

public:

	Model();
	~Model();
	void Update();
	const XMMATRIX& GetWorldMat();
	void AddChild(Model&);
	void RemoveChild(Model&);
	unsigned int GetChildCount() const;
	//giving compile errors TODO
	Model& GetChild(unsigned int) const;
	//Model& const GetChild(unsigned int) const;
};

