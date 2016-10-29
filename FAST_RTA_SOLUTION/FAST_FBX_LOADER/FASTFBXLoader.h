#pragma once

#ifdef FASTFBXLOADER_EXPORTS
#define FASTFBXLOADER_API __declspec(dllexport)
#else
#define FASTFBXLOADER_API __declspec(dllimport)
#endif

#include "FBX_SDK_Includes_Libs\include\fbxsdk.h"
#include <string>

namespace FASTFBXLoader
{
	class FBXLoader
	{
		FbxManager *m_fbxManager;
		FbxScene *m_fbxScene;
		std::string m_inputPath;
		std::string m_outputPath;
		char m_processMasks;

	public:
		FBXLoader();
		bool Init();
		bool Load(const char *_inputPath, const char *_outputPath);

	private:


	};
}
