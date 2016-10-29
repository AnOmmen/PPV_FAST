#include "FASTFBXLoader.h"
#include <DirectXMath.h>
#include <vector>

namespace FASTFBXLoader
{
	FBXLoader::FBXLoader() : m_fbxManager(nullptr), m_fbxScene(nullptr),
		m_processMasks(0) { }

	bool FBXLoader::Init()
	{
		m_fbxManager = FbxManager::Create();
		if (!m_fbxManager)
			return false;

		FbxIOSettings* fbxIOSettings = FbxIOSettings::Create(m_fbxManager, IOSROOT);
		m_fbxManager->SetIOSettings(fbxIOSettings);

		m_fbxScene = FbxScene::Create(m_fbxManager, "_placeHolder");

		return true;
	}

	bool FBXLoader::Load(const char * _inputPath, const char * _outputPath)
	{
		m_inputPath = _inputPath;
		m_outputPath = _outputPath;

		FbxImporter *fbxImporter = FbxImporter::Create(m_fbxManager, "_placeHolder");
		if (!fbxImporter)
			return false;

		if (!fbxImporter->Initialize(_inputPath, -1, m_fbxManager->GetIOSettings()))
			return false;

		if (!fbxImporter->Import(m_fbxScene))
			return false;

		fbxImporter->Destroy();

		return true;
	}
}