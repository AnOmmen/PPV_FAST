#include "Model.h"



void Model::Update(XMMATRIX & _matrix)
{

}

Model::Model(ID3D11Device* device)
{
	m_Mesh = new Mesh(device);
}


Model::~Model()
{
}

void Model::Update()
{
}

const XMMATRIX & Model::GetWorldMat()
{
	// TODO: insert return statement here
	return XMMATRIX();
}

void Model::AddChild(Model &child)
{
}

void Model::RemoveChild(Model &child)
{
}

unsigned int Model::GetChildCount() const
{
	return 0;
}

Model & Model::GetChild(unsigned int) const
{
	// TODO: insert return statement here
	Model temp = *this;
	return temp;
}


unsigned short Model::GetNumMeshIndeces()
{
	return m_Mesh->GetNumIndeces();
}
