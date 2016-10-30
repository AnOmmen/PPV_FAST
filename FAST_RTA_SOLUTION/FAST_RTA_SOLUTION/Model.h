#pragma once

#include "Mesh.h"
class Model
{
private:
	std::vector<Model*> m_children;
	XMMATRIX m_local;
	XMMATRIX m_world;
	Mesh* m_Mesh;
	void Update(XMMATRIX& _matrix);
	Model();
public:

	Model(ID3D11Device* device);
	~Model();
	void Update();
	const XMMATRIX& GetWorldMat();
	void AddChild(Model&);
	void RemoveChild(Model&);
	unsigned int GetChildCount() const;
	//giving compile errors TODO
	Model& GetChild(unsigned int) const;
	//Model& const GetChild(unsigned int) const;
	unsigned short GetNumMeshIndeces();
	ID3D11Buffer** GetVertBuff();
	ID3D11Buffer** GetIndexBuff();

};

