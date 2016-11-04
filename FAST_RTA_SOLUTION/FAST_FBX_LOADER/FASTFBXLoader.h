#pragma once

#define FASTFBXLOADER_EXPORTS
#ifdef FASTFBXLOADER_EXPORTS
#define FASTFBXLOADER_API __declspec(dllexport)
#else
#define FASTFBXLOADER_API __declspec(dllimport)
#endif

#include <vector>

namespace DirectX
{
	struct XMFLOAT4X4;
}

namespace FASTFBXLoader
{
	FASTFBXLOADER_API void Clean();
	FASTFBXLOADER_API bool Init();
	FASTFBXLOADER_API bool Load(const char *_inputPath);
	FASTFBXLOADER_API bool Export(const char *_outputPath);
	FASTFBXLOADER_API bool HasAnimation();
	FASTFBXLOADER_API unsigned int GetTriangleCount();
	FASTFBXLOADER_API std::vector<unsigned short> & GetIndices();
	FASTFBXLOADER_API void * GetKeyFrames();
	FASTFBXLOADER_API unsigned int GetKeyFrameCount();
	FASTFBXLOADER_API void * GetVertices();
	FASTFBXLOADER_API unsigned int GetVertexCount();
	FASTFBXLOADER_API std::vector<DirectX::XMFLOAT4X4> & GetBindPose();
}
