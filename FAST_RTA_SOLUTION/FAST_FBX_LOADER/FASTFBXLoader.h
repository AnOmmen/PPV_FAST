#pragma once

#ifdef FASTFBXLOADER_EXPORTS
#define FASTFBXLOADER_API __declspec(dllexport)
#else
#define FASTFBXLOADER_API __declspec(dllimport)
#endif

#include "FBX_SDK_Includes_Libs\include\fbxsdk.h"
#include "../FAST_RTA_SOLUTION/StructsEnumsDefines.h"
#include "../FAST_RTA_SOLUTION/BindPose.h"
#include <string>
#include <unordered_map>

namespace FASTFBXLoader
{
	class FBXLoader
	{
		FbxManager *m_fbxManager;
		FbxScene *m_fbxScene;
		std::string m_inputPath;
		std::string m_outputPath;
		Skeleton m_skeleton;
		std::vector<std::string> m_skeletonBoneNames;
		BindPose m_skeletonBindPose;
		std::vector<KeyFrame> m_keyFrames;
		std::unordered_map<unsigned int, ControlPoint*> m_controlPoints;
		unsigned int m_triangleCount;
		std::vector<FullVertex> m_vertices;
		std::vector<unsigned int> m_indices;
		bool m_hasAnimation;

	public:
		FBXLoader();
		~FBXLoader();
		bool Init();
		bool Load(const char *_inputPath, const char *_outputPath);
		bool HasAnimation() const;
		unsigned int GetTriangleCount() const;
		std::vector<unsigned int> & GetIndices();
		std::vector<KeyFrame> & GetKeyFrames();
		std::vector<FullVertex> & GetVertices();
		BindPose & GetBindPose();

	private:
		void ProcessSkeleton(FbxNode *_inRootNode);
		void ProcessSKeletonRecursively(FbxNode *_inNode);
		void ProcessGeometry(FbxNode *_inNode);
		void ProcessControlPoints(FbxNode *_inNode);
		void ProcessBonesAndAnimations(FbxNode *_inNode);
		void ProcessMesh(FbxNode *_inNode);
		void ReadNormal(FbxMesh *_inMesh, int _inCtrlPointIndex, int _inVertexCounter, DirectX::XMFLOAT3 &_outNormal);
		void ReadUV(FbxMesh *_inMesh, int _inCtrlPointIndex, int _inTextureUVIndex, int _inUVLayer, DirectX::XMFLOAT2 &_outUV);
		void ReadTangent(FbxMesh *_inMesh, int _inCtrlPointIndex, int _inVertexCounter, DirectX::XMFLOAT3 &_outTangent);
		void SortBlendingInfoByWeight(FullVertex &_vertex);
		void Optimize();
		int FindVertex(const FullVertex &_inTargetVertex, const std::vector<FullVertex> &_uniqueVertices);
		unsigned int FindBoneIndexUsingName(const std::string &_inBoneName);
		FbxAMatrix GetGeometryTransformation(FbxNode *_inNode);
		DirectX::XMMATRIX FBXAMatrixToDXMatrix(FbxAMatrix const &_inMatrix);

	};
}
