#include "PolyShader.h"



PolyShader::PolyShader()
{
	m_modelCount = 0;
	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the Model Class and in the shader.
	m_layout = nullptr;

}


PolyShader::~PolyShader()
{

}

void PolyShader::Render(ID3D11DeviceContext* deviceContext, 
	int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, Model* key)
{
	SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, key);
	RenderShader(deviceContext, indexCount, key);
}


void PolyShader::ShutdownShader(Model* key)
{

	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the layout.
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pixel shader.
	if (m_ps[key])
	{
		m_ps[key]->Release();
		m_ps[key] = 0;
	}

	// Release the vertex shader.
	if (m_vs[key])
	{
		m_vs[key]->Release();
		m_vs[key] = 0;
	}

	// Release the geoshader
	if (m_gs[key])
	{
		m_gs[key]->Release();
		m_gs[key] = 0;
	}

	return;
}

bool PolyShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, Model* key)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr = new MatrixBufferType;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;
	//deviceContext->UpdateSubresource(m_matrixBuffer, 0, 0, dataPtr, 0, 0);
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	
	//delete dataPtr;

	return true;



}

void PolyShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount, Model* key)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	UINT stride = sizeof(Vertex);
	UINT os = 0;
	deviceContext->IASetVertexBuffers(
		0,
		1,
		key->GetVertBuff(),
		&stride,
		&os
	);
	deviceContext->IASetIndexBuffer(
		*key->GetIndexBuff(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).  R32
		0
	);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vs[key], NULL, 0);
	deviceContext->PSSetShader(m_ps[key], NULL, 0);
	// Render the triangle.
	
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}

void PolyShader::AddModel(Model* key, ID3D11VertexShader* _vs,
	ID3D11PixelShader* _ps, ID3D11GeometryShader* _gs, 
	ID3D11Device* device, HWND hwnd, 
	WCHAR* vsFilename, WCHAR* psFilename, WCHAR* gsFilename)
{
   //initialize shader
	
	m_modelCount++;


	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	ID3D10Blob* geoShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements = 0;
	D3D11_BUFFER_DESC* matrixBufferDesc = new D3D11_BUFFER_DESC;


	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;
	geoShaderBuffer = 0;
	//// Compile the vertex shader code.


	//giving linker errors for D3DCompileFromFile

	if(_vs)
	D3DCompileFromFile(vsFilename, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	// Compile the pixel shader code.
	if (_ps)
	D3DCompileFromFile(psFilename, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	// Compile the geometry shader code.
	if (_gs)
	D3DCompileFromFile(gsFilename, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "gs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0,
		&geoShaderBuffer, &errorMessage);
	


	bool vs, ps, gs;
	vs = ps = gs = false;
	// Create the vertex shader from the buffer.
	for (auto i = m_vs.begin(); i != m_vs.end(); ++i)
	{
		if (i->second == _vs)
			vs = true;
	}
	for (auto i = m_ps.begin(); i != m_ps.end(); ++i)
	{
		if (i->second == _ps)
			ps = true;
	}
	for (auto i = m_gs.begin(); i != m_gs.end(); ++i)
	{
		if (i->second == _gs)
			gs = true;
	}
 	if (!vs && _vs)
	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &_vs);
	// Create the pixel shader from the buffer.
	if (!ps && _ps)
	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &_ps);
	// Create the geometry shader from the buffer.
	if (!gs && _gs)
	device->CreateGeometryShader(geoShaderBuffer->GetBufferPointer(), geoShaderBuffer->GetBufferSize(), NULL, &_gs);

	if (_vs)
	{
		m_vs[key] = _vs;
	}
	if (_ps)
	{
		m_ps.emplace(key, _ps);
	}
	if (_gs)
	{
		m_gs.emplace(key, _gs);
	}

	if (!m_layout)
	{
		polygonLayout[numElements].SemanticName = "POSITION";
		polygonLayout[numElements].SemanticIndex = 0;
		polygonLayout[numElements].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		polygonLayout[numElements].InputSlot = 0;
		polygonLayout[numElements].AlignedByteOffset = 0;
		polygonLayout[numElements].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[numElements].InstanceDataStepRate = 0;
		numElements++;

		// Create the pixel input layout description.
		// This setup needs to match the VertexType stucture in the Model Class and in the shader.

		polygonLayout[numElements].SemanticName = "COLOR";
		polygonLayout[numElements].SemanticIndex = 0;
		polygonLayout[numElements].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		polygonLayout[numElements].InputSlot = 0;
		polygonLayout[numElements].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[numElements].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[numElements].InstanceDataStepRate = 0;
		numElements++;

		polygonLayout[numElements].SemanticName = "NORMAL";
		polygonLayout[numElements].SemanticIndex = 0;
		polygonLayout[numElements].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		polygonLayout[numElements].InputSlot = 0;
		polygonLayout[numElements].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[numElements].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[numElements].InstanceDataStepRate = 0;
		numElements++;
		// Create the vertex input layout.
		device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), &m_layout);


		matrixBufferDesc->Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc->ByteWidth = sizeof(MatrixBufferType);
		matrixBufferDesc->BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc->CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc->MiscFlags = 0;
		matrixBufferDesc->StructureByteStride = 0;

		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.

		HRESULT hresult = device->CreateBuffer(matrixBufferDesc, NULL, &m_matrixBuffer);



		numElements = 0;
	}


	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	if(vertexShaderBuffer)
	vertexShaderBuffer->Release();
	if(pixelShaderBuffer)
	pixelShaderBuffer->Release();
	if(geoShaderBuffer)
	geoShaderBuffer->Release();



	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.





}

void PolyShader::RemoveModel(Model * key)
{
	ShutdownShader(key);
}

unsigned int PolyShader::GetModelCount() const
{

	return m_modelCount;
}

ID3D11VertexShader const * PolyShader::GetVS(Model* key) const
{
	return m_vs.at(key);
}

ID3D11PixelShader const * PolyShader::GetPS(Model* key) const
{
	return m_ps.at(key);
}

ID3D11GeometryShader const * PolyShader::GetGS(Model* key) const
{
	return m_gs.at(key);
}
