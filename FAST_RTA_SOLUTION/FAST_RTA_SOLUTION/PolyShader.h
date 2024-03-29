#pragma once
#include "Model.h"
#include <unordered_map>
#include <d3dcompiler.h>
#include "BindPose.h"
#include "Blender.h"
#pragma comment(lib, "d3dcompiler.lib")
#include <fstream>
using namespace DirectX;
class PolyShader
{
private:

	std::unordered_map<Model*, ID3D11VertexShader*> m_vs;
	std::unordered_map<Model*, ID3D11PixelShader*> m_ps;
	std::unordered_map<Model*, ID3D11GeometryShader*> m_gs;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_changeBuffer;

	struct MatrixBufferType
	{
		XMMATRIX world[5];
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct ChangeBufferType
	{
		XMFLOAT4X4 BoneOffset[37];
	};
	unsigned int m_modelCount;
	unsigned int tempcounter;

	void ShutdownShader(Model* key);
	bool SetShaderParameters(ID3D11DeviceContext*, std::vector<XMMATRIX>&, XMMATRIX, XMMATRIX, Model* key, Blender*);
	void RenderShader(ID3D11DeviceContext*, int, Model* key);

public:
	XMFLOAT4X4 offsets[32];
	PolyShader();
	~PolyShader();

	void AddModel(Model* key, ID3D11VertexShader* _vs,
		ID3D11PixelShader* _ps, ID3D11GeometryShader* _gs,
		ID3D11Device* device, HWND hwnd,
		WCHAR* vsFilename, WCHAR* psFilename, WCHAR* gsFilename);
	void RemoveModel(Model*);
	unsigned int GetModelCount() const;
	ID3D11VertexShader const* GetVS(Model*) const;
	ID3D11PixelShader const* GetPS(Model*) const;
	ID3D11GeometryShader const* GetGS(Model*) const;
	void Render(ID3D11DeviceContext* deviceContext, int indexCount, std::vector<XMMATRIX> &worldMatrix, XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix, Model* key, Blender* blender);


};

