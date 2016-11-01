#include "Model.h"



void Model::Update(DirectX::XMMATRIX & _matrix)
{
	//the parent passes their updated matrix to each child
	//child must update their world matrix according to the parent's matrix
	//child must also change their local matrix based on the changes
}

Model::Model()
{
	m_local = DirectX::XMMatrixIdentity();
	m_world = DirectX::XMMatrixIdentity();
}


Model::~Model()
{

}

void Model::Update()
{
	//stuff that we havent decided yet

}

const DirectX::XMMATRIX & Model::GetWorldMat()
{
	return m_world;
}
//Adds a single model to the vector of children by pushing onto the back of the vector.
unsigned int Model::AddChild(Model &_mod)
{
	m_children.push_back(&_mod);
	unsigned int index;
	index = m_children.size() - 1;
	return index;
}
//is passed an index of the children vector correlating to the correct child to remove
//copies the current vector to a new vector, excluding the child to be removed.
void Model::RemoveChild(unsigned int _index)
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
	return *m_children[_index];
}


unsigned short Model::GetNumIndeces()
{
	return m_Mesh->GetNumIndeces();
}