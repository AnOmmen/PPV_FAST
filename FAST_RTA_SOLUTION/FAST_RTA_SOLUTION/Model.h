#pragma once
#include "Mesh.h"
#include "StructsEnumsDefines.h"

class Model
{
private:
	std::vector<Model*> m_children;
	DirectX::XMMATRIX m_local;
	DirectX::XMMATRIX m_world;
	Mesh* m_Mesh;
	void Update(DirectX::XMMATRIX& _matrix);
public:
	Model();
	~Model();
	void Update();
	const DirectX::XMMATRIX& GetWorldMat();
	unsigned int AddChild(Model& _mod);
	void RemoveChild(unsigned int _index);
	size_t GetChildCount() const;
	//giving compile errors TODO
	Model& GetChild(unsigned int _index) const;
	//Model& const GetChild(unsigned int) const;
};

