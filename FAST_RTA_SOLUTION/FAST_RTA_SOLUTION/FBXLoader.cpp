#include "FASTFBXLoader.h"

namespace FASTFBXLoader
{
	FBXLoader::FBXLoader() : m_fbxManager(nullptr), m_fbxScene(nullptr) { }

	FBXLoader::~FBXLoader()
	{
		m_fbxScene->Destroy();
		m_fbxManager->Destroy();
		m_indices.clear();
		m_vertices.clear();
		m_skeleton.sk.clear();
	}

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

		ProcessSkeleton(m_fbxScene->GetRootNode());
		if (m_skeleton.sk.empty())
			m_hasAnimation = false;
		else
			m_hasAnimation = true;

		ProcessGeometry(m_fbxScene->GetRootNode());
		Optimize();

		return true;
	}

	bool FBXLoader::HasAnimation() const
	{
		return m_hasAnimation;
	}

	unsigned int FBXLoader::GetTriangleCount() const
	{
		return m_triangleCount;
	}

	std::vector<unsigned int>& FBXLoader::GetIndices()
	{
		return m_indices;
	}

	std::vector<KeyFrame>& FBXLoader::GetKeyFrames()
	{
		return m_keyFrames;
	}

	std::vector<FullVertex>& FBXLoader::GetVertices()
	{
		return m_vertices;
	}

	BindPose & FBXLoader::GetBindPose()
	{
		return m_skeletonBindPose;
	}

	void FBXLoader::ProcessSkeleton(FbxNode * _inRootNode)
	{
		unsigned int i;
		for (i = 0; i < _inRootNode->GetChildCount(); ++i)
		{
			FbxNode* currNode = _inRootNode->GetChild(i);

		}
	}

	void FBXLoader::ProcessSKeletonRecursively(FbxNode * _inNode)
	{
		if (_inNode->GetNodeAttribute() && _inNode->GetNodeAttribute()->GetAttributeType() &&
			_inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			Bone currBone;
			m_skeleton.sk.push_back(currBone);
			std::string currName = _inNode->GetName();
			m_skeletonBoneNames.push_back(currName);
		}

		unsigned int i;
		for (i = 0; i < _inNode->GetChildCount(); ++i)
			ProcessSKeletonRecursively(_inNode->GetChild(i));
	}

	void FBXLoader::ProcessGeometry(FbxNode * _inNode)
	{
		if (_inNode->GetNodeAttribute())
			switch (_inNode->GetNodeAttribute()->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
				ProcessControlPoints(_inNode);
				if (m_hasAnimation)
					ProcessBonesAndAnimations(_inNode);
				ProcessMesh(_inNode);
				break;
			}

		for (int i = 0; i < _inNode->GetChildCount(); ++i)
			ProcessGeometry(_inNode->GetChild(i));
	}

	void FBXLoader::ProcessControlPoints(FbxNode * _inNode)
	{
		FbxMesh* currMesh = _inNode->GetMesh();
		unsigned int i;
		for (i = 0; i < currMesh->GetControlPointsCount(); ++i)
		{
			ControlPoint *currCtrlPoint = new ControlPoint();
			currCtrlPoint->position.x = static_cast<float>(currMesh->GetControlPointAt(i).mData[0]);
			currCtrlPoint->position.y = static_cast<float>(currMesh->GetControlPointAt(i).mData[1]);
			currCtrlPoint->position.z = static_cast<float>(currMesh->GetControlPointAt(i).mData[2]);
			m_controlPoints[i] = currCtrlPoint;
		}
	}

	void FBXLoader::ProcessBonesAndAnimations(FbxNode * _inNode)
	{
		FbxMesh *currMesh = _inNode->GetMesh();
		unsigned int numbOfDeformers = currMesh->GetDeformerCount();
		FbxAMatrix geometryTransform = GetGeometryTransformation(_inNode);

		unsigned int deformerIndex;
		for (deformerIndex = 0; deformerIndex < numbOfDeformers; ++deformerIndex)
		{
			FbxSkin *currSkin =
				reinterpret_cast<FbxSkin*>(currMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
			if (!currSkin)
				continue;

			m_skeletonBindPose.bindposeInverses.resize(m_skeleton.sk.size());
			FbxAnimStack *currAnimStack = m_fbxScene->GetSrcObject<FbxAnimStack>(0);
			FbxString animStackName = currAnimStack->GetName();
			FbxTakeInfo *takeInfo = m_fbxScene->GetTakeInfo(animStackName.Buffer());
			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
			for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24);
				i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
			{
				KeyFrame tempKF;
				FbxTime currTime;
				currTime.SetFrame(i, FbxTime::eFrames24);
				tempKF.m_time = (float)currTime.GetSecondDouble();

				unsigned int clusterIndex, numOfClusters = currSkin->GetClusterCount();
				for (clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
				{
					FbxCluster *currCluster = currSkin->GetCluster(clusterIndex);
					std::string currBoneName = currCluster->GetLink()->GetName();
					unsigned int currBoneIndex = FindBoneIndexUsingName(currBoneName);
					FbxAMatrix transformMatrix;
					FbxAMatrix transformLinkMatrix;
					FbxAMatrix globalBindposeInverseMatrix;

					currCluster->GetTransformMatrix(transformMatrix);
					currCluster->GetTransformLinkMatrix(transformLinkMatrix);
					globalBindposeInverseMatrix = transformLinkMatrix.Inverse() *
						transformMatrix * geometryTransform;

					// ONLY DO THIS ONCE
					if (start.GetFrameCount(FbxTime::eFrames24) == i)
						m_skeletonBindPose.bindposeInverses[currBoneIndex] =
						FBXAMatrixToDXMatrix(globalBindposeInverseMatrix);

					unsigned int j, numOfIndices = currCluster->GetControlPointIndicesCount();
					for (j = 0; j < numOfIndices; ++j)
					{
						int ctrlPointIndex = currCluster->GetControlPointIndices()[j];
						m_controlPoints[ctrlPointIndex]->bIndices.push_back(currBoneIndex);
						m_controlPoints[ctrlPointIndex]->bWeights.push_back(currCluster->GetControlPointWeights()[j]);
					}

					FbxAMatrix currentTransfromOffset = _inNode->EvaluateGlobalTransform(currTime) * geometryTransform;
					Bone tempBone;
					tempBone.m_world = FBXAMatrixToDXMatrix(
						currentTransfromOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(currTime)
					);
					tempKF.m_skeleton.sk.push_back(tempBone);
				}
			}
		}

		for (auto itr = m_controlPoints.begin(); itr != m_controlPoints.end(); ++itr)
		{
			for (unsigned int i = itr->second->bIndices.size(); i <= 4; ++i)
				itr->second->bIndices.push_back(0);
			for (unsigned int i = itr->second->bWeights.size(); i <= 4; ++i)
				itr->second->bWeights.push_back(0);
		}
	}

	void FBXLoader::ProcessMesh(FbxNode * _inNode)
	{
		FbxMesh *currMesh = _inNode->GetMesh();
		m_triangleCount = currMesh->GetPolygonCount();
		int vertexCounter = 0;

		unsigned int i, j;
		for (i = 0; i < m_triangleCount; ++i)
		{
			DirectX::XMFLOAT3 normal[3];
			DirectX::XMFLOAT3 tangent[3];
			DirectX::XMFLOAT2 UV[3];

			for (j = 0; j < 3; ++j)
			{
				int ctrlPointIndex = currMesh->GetPolygonVertex(i, j);
				ControlPoint *currCtrlPoint = m_controlPoints[ctrlPointIndex];

				ReadNormal(currMesh, ctrlPointIndex, vertexCounter, normal[j]);
				ReadUV(currMesh, ctrlPointIndex, currMesh->GetTextureUVIndex(i, j), 0, UV[j]);
				ReadTangent(currMesh, ctrlPointIndex, vertexCounter, tangent[j]);

				FullVertex temp;
				temp.pos = currCtrlPoint->position;
				temp.norm = normal[j];
				temp.uv = UV[j];
				temp.tan = tangent[j];

				temp.bIndices.x = currCtrlPoint->bIndices[0];
				temp.bIndices.y = currCtrlPoint->bIndices[1];
				temp.bIndices.z = currCtrlPoint->bIndices[2];
				temp.bIndices.w = currCtrlPoint->bIndices[3];

				temp.bWeights.x = currCtrlPoint->bWeights[0];
				temp.bWeights.y = currCtrlPoint->bWeights[1];
				temp.bWeights.z = currCtrlPoint->bWeights[2];
				temp.bWeights.w = currCtrlPoint->bWeights[3];

				SortBlendingInfoByWeight(temp);
				m_vertices.push_back(temp);
				m_indices.push_back(vertexCounter++);
			}
		}

		for (auto itr = m_controlPoints.begin(); itr != m_controlPoints.end(); ++itr)
			delete itr->second;
		m_controlPoints.clear();
	}

	void FBXLoader::ReadNormal(FbxMesh *_inMesh, int _inCtrlPointIndex, int _inVertexCounter, DirectX::XMFLOAT3 &_outNormal)
	{
		FbxGeometryElementNormal* vertexNormal = _inMesh->GetElementNormal(0);
		switch (vertexNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				_outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(_inCtrlPointIndex).mData[0]);
				_outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(_inCtrlPointIndex).mData[1]);
				_outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(_inCtrlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(_inCtrlPointIndex);
				_outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				_outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				_outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				break;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				_outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(_inVertexCounter).mData[0]);
				_outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(_inVertexCounter).mData[1]);
				_outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(_inVertexCounter).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(_inVertexCounter);
				_outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				_outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				_outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				break;
			}
			break;
		}
	}

	void FBXLoader::ReadUV(FbxMesh * _inMesh, int _inCtrlPointIndex, int _inTextureUVIndex, int _inUVLayer, DirectX::XMFLOAT2 & _outUV)
	{
		FbxGeometryElementUV *vertexUV = _inMesh->GetElementUV(_inUVLayer);
		switch (vertexUV->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				_outUV.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(_inCtrlPointIndex).mData[0]);
				_outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(_inCtrlPointIndex).mData[1]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexUV->GetIndexArray().GetAt(_inCtrlPointIndex);
				_outUV.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
				_outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
			}
			break;

			default:
				break;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			case FbxGeometryElement::eIndexToDirect:
			{
				_outUV.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(_inTextureUVIndex).mData[0]);
				_outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(_inTextureUVIndex).mData[1]);
			}
			break;

			default:
				break;
			}
			break;
		}
	}

	void FBXLoader::ReadTangent(FbxMesh * _inMesh, int _inCtrlPointIndex, int _inVertexCounter, DirectX::XMFLOAT3 & _outTangent)
	{
		FbxGeometryElementTangent *vertexTangent = _inMesh->GetElementTangent(0);
		switch (vertexTangent->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				_outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(_inCtrlPointIndex).mData[0]);
				_outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(_inCtrlPointIndex).mData[1]);
				_outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(_inCtrlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexTangent->GetIndexArray().GetAt(_inCtrlPointIndex);
				_outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				_outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				_outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				break;
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				_outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(_inVertexCounter).mData[0]);
				_outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(_inVertexCounter).mData[1]);
				_outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(_inVertexCounter).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexTangent->GetIndexArray().GetAt(_inVertexCounter);
				_outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				_outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				_outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				break;
			}
			break;
		}
	}

	void FBXLoader::SortBlendingInfoByWeight(FullVertex & _vertex)
	{
		float indices[4] =
		{
			_vertex.bIndices.x,
			_vertex.bIndices.y,
			_vertex.bIndices.z,
			_vertex.bIndices.w
		};

		float weights[4] =
		{
			_vertex.bWeights.x,
			_vertex.bWeights.y,
			_vertex.bWeights.z,
			_vertex.bWeights.w
		};

		unsigned int i, j;
		for (i = 0; i < 4; ++i)
			for (j = i + 1; j < 4; ++j)
				if (weights[i] > weights[j])
				{
					float temp = weights[i];
					weights[i] = weights[j];
					weights[j] = temp;
					temp = indices[i];
					indices[i] = indices[j];
					indices[j] = temp;
				}

		_vertex.bIndices.x = indices[0];
		_vertex.bIndices.y = indices[1];
		_vertex.bIndices.z = indices[2];
		_vertex.bIndices.w = indices[3];

		_vertex.bWeights.x = weights[0];
		_vertex.bWeights.y = weights[1];
		_vertex.bWeights.z = weights[2];
		_vertex.bWeights.w = weights[3];
	}

	void FBXLoader::Optimize()
	{
		std::vector<FullVertex> uniqueVertices;
		unsigned int i, j;
		for (i = 0; i < m_triangleCount; ++i)
			for (j = 0; j < 3; ++j)
				if (FindVertex(m_vertices[i * 3 + j], uniqueVertices) == -1)
					uniqueVertices.push_back(m_vertices[i * 3 + j]);

		for (i = 0; i < m_triangleCount; ++i)
			for (j = 0; j < 3; ++j)
				m_indices[i * 3 + j] = FindVertex(m_vertices[i * 3 + j], uniqueVertices);

		m_vertices.clear();
		m_vertices = uniqueVertices;
		uniqueVertices.clear();
	}

	int FBXLoader::FindVertex(const FullVertex & _inTargetVertex, const std::vector<FullVertex>& _uniqueVertices)
	{
		unsigned int i;
		for (i = 0; i < _uniqueVertices.size(); ++i)
			if (_inTargetVertex.pos.x == _uniqueVertices[i].pos.x &&
				_inTargetVertex.pos.y == _uniqueVertices[i].pos.y &&
				_inTargetVertex.pos.z == _uniqueVertices[i].pos.z &&
				_inTargetVertex.norm.x == _uniqueVertices[i].norm.x &&
				_inTargetVertex.norm.y == _uniqueVertices[i].norm.y &&
				_inTargetVertex.norm.z == _uniqueVertices[i].norm.z &&
				_inTargetVertex.tan.x == _uniqueVertices[i].tan.x &&
				_inTargetVertex.tan.y == _uniqueVertices[i].tan.y &&
				_inTargetVertex.tan.z == _uniqueVertices[i].tan.z &&
				_inTargetVertex.uv.x == _uniqueVertices[i].uv.x &&
				_inTargetVertex.uv.y == _uniqueVertices[i].uv.y &&
				_inTargetVertex.bWeights.x == _uniqueVertices[i].bWeights.x &&
				_inTargetVertex.bWeights.y == _uniqueVertices[i].bWeights.y &&
				_inTargetVertex.bWeights.z == _uniqueVertices[i].bWeights.z &&
				_inTargetVertex.bWeights.w == _uniqueVertices[i].bWeights.w &&
				_inTargetVertex.bIndices.x == _uniqueVertices[i].bIndices.x &&
				_inTargetVertex.bIndices.y == _uniqueVertices[i].bIndices.y &&
				_inTargetVertex.bIndices.z == _uniqueVertices[i].bIndices.z &&
				_inTargetVertex.bIndices.w == _uniqueVertices[i].bIndices.w)
				return i;
	}

	unsigned int FBXLoader::FindBoneIndexUsingName(const std::string & _inBoneName)
	{
		unsigned int i;
		for (i = 0; i < m_skeletonBoneNames.size(); ++i)
			if (_inBoneName == m_skeletonBoneNames[i])
				return i;
		return UINT32_MAX;
	}

	FbxAMatrix FBXLoader::GetGeometryTransformation(FbxNode * _inNode)
	{
		if (!_inNode)
			return FbxAMatrix();

		const FbxVector4 lT = _inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = _inNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = _inNode->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(lT, lR, lS);
	}

	DirectX::XMMATRIX FBXLoader::FBXAMatrixToDXMatrix(FbxAMatrix const & _inMatrix)
	{
		DirectX::XMMATRIX retMatrix;
		retMatrix.r[0].m128_f32[0] = (float)_inMatrix.mData[0].mData[0];
		retMatrix.r[0].m128_f32[1] = (float)_inMatrix.mData[0].mData[1];
		retMatrix.r[0].m128_f32[2] = (float)_inMatrix.mData[0].mData[2];
		retMatrix.r[0].m128_f32[3] = (float)_inMatrix.mData[0].mData[3];

		retMatrix.r[1].m128_f32[0] = (float)_inMatrix.mData[1].mData[0];
		retMatrix.r[1].m128_f32[1] = (float)_inMatrix.mData[1].mData[1];
		retMatrix.r[1].m128_f32[2] = (float)_inMatrix.mData[1].mData[2];
		retMatrix.r[1].m128_f32[3] = (float)_inMatrix.mData[1].mData[3];

		retMatrix.r[2].m128_f32[0] = (float)_inMatrix.mData[2].mData[0];
		retMatrix.r[2].m128_f32[1] = (float)_inMatrix.mData[2].mData[1];
		retMatrix.r[2].m128_f32[2] = (float)_inMatrix.mData[2].mData[2];
		retMatrix.r[2].m128_f32[3] = (float)_inMatrix.mData[2].mData[3];

		retMatrix.r[3].m128_f32[0] = (float)_inMatrix.mData[3].mData[0];
		retMatrix.r[3].m128_f32[1] = (float)_inMatrix.mData[3].mData[1];
		retMatrix.r[3].m128_f32[2] = (float)_inMatrix.mData[3].mData[2];
		retMatrix.r[3].m128_f32[3] = (float)_inMatrix.mData[3].mData[3];

		return retMatrix;
	}
}