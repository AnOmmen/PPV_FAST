#include "Model.h"



void Model::Update(XMMATRIX & _matrix)
{
	//the parent passes their updated matrix to each child
	//child must update their world matrix according to the parent's matrix
	//child must also change their local matrix based on the changes
}

Model::Model(ID3D11Device* device)
{
	m_local = XMMatrixIdentity();
	m_world = XMMatrixIdentity();
	m_Mesh = new Mesh(device);
}


Model::~Model()
{

}

void Model::Update()
{
	//stuff that we havent decided yet
}

const XMMATRIX & Model::GetWorldMat()
{

	
	// TODO: insert return statement here
	return XMMatrixIdentity();
}
//Adds a single model to the vector of children by pushing onto the back of the vector.
unsigned int Model::AddChild(Model &_mod)

void Model::AddChild(Model &child)
{
	m_children.push_back(&_mod);
	unsigned int index;
	index = m_children.size() - 1;
	return index;
}
//is passed an index of the children vector correlating to the correct child to remove
//copies the current vector to a new vector, excluding the child to be removed.
void Model::RemoveChild(unsigned int _index)

void Model::RemoveChild(Model &child)
{
	
	std::vector<Model*> updatedVec;
	for (unsigned int i = 0; i < m_children.size(); ++i)
	{
		if (i == _index)
		{
			continue;
		}
		updatedVec.push_back(m_children[i]);
	}
	m_children = updatedVec;
}

size_t Model::GetChildCount() const
{
	return m_children.size();
}

Model& Model::GetChild(unsigned int _index) const
{
	// TODO: insert return statement here
	Model temp = *this;
	return temp;
}


unsigned short Model::GetNumMeshIndeces()
{
	return m_Mesh->GetNumIndeces();
}


ID3D11Buffer** Model::GetVertBuff()
{
	return m_Mesh->GetVertBuff();
}
ID3D11Buffer** Model::GetIndexBuff()
{
	return m_Mesh->GetIndexBuff();
}