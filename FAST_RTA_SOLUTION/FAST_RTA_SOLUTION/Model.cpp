#include "Model.h"



void Model::Update(DirectX::XMMATRIX & _matrix)
{
	//the parent passes their updated matrix to each child
	//child must update their world matrix according to the parent's matrix
	//child must also change their local matrix based on the changes
	m_world = XMMatrixMultiply(m_local, _matrix);

}

Model::Model()
{


}
Model::Model(ID3D11Device* device, std::vector<FullVertex> &_vertices, std::vector<unsigned short> &_indices)
{
	hasAnimation = false;
	m_Mesh = new Mesh(device);
	m_world = DirectX::XMMatrixIdentity();
	m_local = DirectX::XMMatrixIdentity();
	shaderview = nullptr;
	timesToDraw = 0;
	if (!_vertices.empty())
	{
		m_Mesh->CreateMesh(device, _vertices, _indices);
	}
	
}

Model::~Model()
{
	delete m_Mesh;
}

void Model::Update(float dt)
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
	index = (unsigned int)m_children.size() - 1;
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


ID3D11Buffer** Model::GetVertBuffer()
{
	return m_Mesh->Mesh::GetVertBuff();
}


ID3D11Buffer** Model::GetIndexBuffer()
{
	return m_Mesh->Mesh::GetIndexBuff();
}

void Model::LoadAnimation(const char* _filePath, ID3D11Device* device)
{
	unsigned short* tempin;
	FullVertex* tempvert;
	unsigned long tempnum;
	unsigned long tempnumverts;
	m_animSet.LoadAnimationFile(_filePath, &tempin, &tempnum, &tempvert, &tempnumverts);
	std::vector<FullVertex> _vertices;
	std::vector<unsigned short> _indeces;
	for (size_t i = 0; i < tempnumverts; i++)
	{
		_vertices.push_back(tempvert[i]);
	}
	for (size_t i = 0; i < tempnum; i++)
	{
		_indeces.push_back(tempin[i]);
	}
	delete[] tempin;
	delete[] tempvert;
	m_Mesh->CreateMesh(device, _vertices, _indeces);

}


AnimationSet &Model::GetAnimationSet()
{
	return m_animSet;
}
