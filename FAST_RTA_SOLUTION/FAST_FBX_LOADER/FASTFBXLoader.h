#pragma once

#define FASTFBXLOADER_EXPORTS
#ifdef FASTFBXLOADER_EXPORTS
#define FASTFBXLOADER_API __declspec(dllexport)
#else
#define FASTFBXLOADER_API __declspec(dllimport)
#endif

#include <vector>

namespace fbxsdk
{
	class FbxNode;
	class FbxMesh;
	class FbxAMatrix;
}

namespace DirectX
{
	struct XMFLOAT2;
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct XMFLOAT4X4;
}

namespace FASTFBXLoader
{
	namespace FBXLoaderStructs
	{
		struct FullVertex;
	}

	FASTFBXLOADER_API void Clean();
	FASTFBXLOADER_API bool Init();
	FASTFBXLOADER_API bool Load(const char *_inputPath, const char *_outputPath);
	FASTFBXLOADER_API bool HasAnimation();
	FASTFBXLOADER_API unsigned int GetTriangleCount();
	FASTFBXLOADER_API std::vector<unsigned short> & GetIndices();
	FASTFBXLOADER_API void * GetKeyFrames();
	FASTFBXLOADER_API unsigned int GetKeyFrameCount();
	FASTFBXLOADER_API void * GetVertices();
	FASTFBXLOADER_API unsigned int GetVertexCount();
	FASTFBXLOADER_API std::vector<DirectX::XMFLOAT4X4> & GetBindPose();
	
	void ProcessSkeleton(fbxsdk::FbxNode *_inRootNode);
	void ProcessSKeletonRecursively(fbxsdk::FbxNode *_inNode);
	void ProcessGeometry(fbxsdk::FbxNode *_inNode);
	void ProcessControlPoints(fbxsdk::FbxNode *_inNode);
	void ProcessBonesAndAnimations(fbxsdk::FbxNode *_inNode);
	void ProcessMesh(fbxsdk::FbxNode *_inNode);
	void ReadNormal(fbxsdk::FbxMesh *_inMesh, int _inCtrlPointIndex, int _inVertexCounter, DirectX::XMFLOAT3 &_outNormal);
	void ReadUV(fbxsdk::FbxMesh *_inMesh, int _inCtrlPointIndex, int _inTextureUVIndex, int _inUVLayer, DirectX::XMFLOAT2 &_outUV);
	void ReadTangent(fbxsdk::FbxMesh *_inMesh, int _inCtrlPointIndex, int _inVertexCounter, DirectX::XMFLOAT3 &_outTangent);
	void SortBlendingInfoByWeight(FBXLoaderStructs::FullVertex &_vertex);
	void Optimize();
	unsigned short FindVertex(const FBXLoaderStructs::FullVertex &_inTargetVertex, const std::vector<FBXLoaderStructs::FullVertex> &_uniqueVertices);
	unsigned int FindBoneIndexUsingName(const std::string &_inBoneName);
	fbxsdk::FbxAMatrix GetGeometryTransformation(fbxsdk::FbxNode *_inNode);
	DirectX::XMFLOAT4X4 FBXAMatrixToDXMatrix(fbxsdk::FbxAMatrix const &_inMatrix);
}
