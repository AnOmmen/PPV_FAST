//struct ANIMATED_LIT_INPUT
//{
//    float3 pos : POSITION0;
//    float2 uv : TEXCOORD0;
//    float4 blendWeights : BLENDWEIGHT0;
//    uint4 boneIndices : BLENDINDICES0;
//    float4 color : NORMAL;
//    float4 world : WORLDMATRIX;
//};
//
//struct PSINPUT
//{
//    float4 position : SV_POSITION;
//    float4 color : COLOR;
//    float4 normal : NORMAL;
//    float4 world : WORLDMATRIX;
//};
//
//
//cbuffer cbChangesEveryFrame : register(b0)
//{
//    matrix BoneOffset[100];
//};
//
//PSINPUT main(ANIMATED_LIT_INPUT input : POSITION) : SV_POSITION
//{
//    PSINPUT output;
//    float4 temp = float4(input.pos, 1.0f);
//    float4x4 VertexOut = (temp * input.blendWeights.x) * BoneOffset[input.boneIndices];
//    VertexOut += (temp * input.blendWeights.y) * BoneOffset[input.boneIndices];
//    VertexOut += (temp * input.blendWeights.z) * BoneOffset[input.boneIndices];
//    VertexOut += (temp * input.blendWeights.w) * BoneOffset[input.boneIndices];
//
//	return output;
//}
