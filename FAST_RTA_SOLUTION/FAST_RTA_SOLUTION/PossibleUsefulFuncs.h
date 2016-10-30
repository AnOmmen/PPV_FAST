#pragma once
// A function to calculate tangents based on given info within the interleaved_index vector
//void Model::TanCalc()
//{
//	DirectX::XMFLOAT3 vert0, vert1, vert2;
//	DirectX::XMFLOAT3 vertEdge0, vertEdge1;
//	DirectX::XMFLOAT2 tex0, tex1, tex2;
//	DirectX::XMFLOAT2 texEdge0, texEdge1;
//	float texRatio;
//	for (int i = 0; i < interleaved_index.size(); i += 3)
//	{
//		vert0 = interleaved_verts[interleaved_index[i]].pos;
//		vert1 = interleaved_verts[interleaved_index[i + 1]].pos;
//		vert2 = interleaved_verts[interleaved_index[i + 2]].pos;
//		XMStoreFloat3(&vertEdge0, XMVectorSubtract(XMLoadFloat3(&vert1), XMLoadFloat3(&vert0)));
//		XMStoreFloat3(&vertEdge1, XMVectorSubtract(XMLoadFloat3(&vert2), XMLoadFloat3(&vert0)));
//		tex0 = interleaved_verts[interleaved_index[i]].uv;
//		tex1 = interleaved_verts[interleaved_index[i + 1]].uv;
//		tex2 = interleaved_verts[interleaved_index[i + 2]].uv;
//		XMStoreFloat2(&texEdge0, XMVectorSubtract(XMLoadFloat2(&tex1), XMLoadFloat2(&tex0)));
//		XMStoreFloat2(&texEdge1, XMVectorSubtract(XMLoadFloat2(&tex2), XMLoadFloat2(&tex0)));
//
//		texRatio = 1.0f / ((texEdge0.x * texEdge1.y) - (texEdge1.x * texEdge0.y));
//
//		XMFLOAT3 uDirection = XMFLOAT3(
//			(texEdge1.y * vertEdge0.x) - (texEdge0.y * vertEdge1.x) * texRatio,
//			(texEdge1.y * vertEdge0.y) - (texEdge0.y * vertEdge1.y) * texRatio,
//			(texEdge1.y * vertEdge0.z) - (texEdge0.y * vertEdge1.z) * texRatio);
//
//		XMFLOAT3 vDirection = XMFLOAT3(
//			(texEdge0.x * vertEdge1.x) - (texEdge1.x * vertEdge0.x) * texRatio,
//			(texEdge0.x * vertEdge1.y) - (texEdge1.x * vertEdge0.y) * texRatio,
//			(texEdge0.x * vertEdge1.z) - (texEdge1.x * vertEdge0.z) * texRatio);
//
//
//
//		for (int j = 0; j < 3; ++j)
//		{
//
//			XMVECTOR uNorm = XMVector3Normalize(XMLoadFloat3(&uDirection));
//			XMVECTOR dotResult = XMVector3Dot(XMLoadFloat3(&interleaved_verts[interleaved_index[i + j]].norm), uNorm);
//			XMVECTOR Tangent = XMVectorSubtract(XMLoadFloat3(&uDirection), XMVectorScale(uNorm, dotResult.m128_f32[0]));
//
//			Tangent = XMVector3Normalize(Tangent);
//
//			XMVECTOR vNorm = XMVector3Normalize(XMLoadFloat3(&vDirection));
//			XMVECTOR cross = XMVector3Cross(XMLoadFloat3(&interleaved_verts[interleaved_index[i + j]].norm), uNorm);
//			XMVECTOR handedness = XMLoadFloat3(&vDirection);
//			dotResult = XMVector3Dot(cross, handedness);
//			Tangent.m128_f32[3] = (dotResult.m128_f32[0] < 0.0f) ? -1.0f : 1.0f;
//
//			interleaved_verts[interleaved_index[i + j]].tan.x = Tangent.m128_f32[0];
//			interleaved_verts[interleaved_index[i + j]].tan.y = Tangent.m128_f32[1];
//			interleaved_verts[interleaved_index[i + j]].tan.z = Tangent.m128_f32[2];
//		}
//
//
//	}
//}



//