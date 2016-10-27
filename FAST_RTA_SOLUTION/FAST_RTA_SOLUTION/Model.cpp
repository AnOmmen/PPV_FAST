#include "Model.h"



void Model::Update(XMMATRIX & _matrix)
{
}

Model::Model()
{
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

void Model::AddChild(Model &)
{
}

void Model::RemoveChild(Model &)
{
}

unsigned int Model::GetChildCount() const
{
	return 0;
}

Model & Model::GetChild(unsigned int) const
{
	// TODO: insert return statement here
	return Model();
}
