struct ANIMATED_LIT_INPUT
{
    float3 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 blendWeights : BWEIGHTS;
    float4 boneIndices : BINDICES;
};

struct PSINPUT
{
    float4 position : SV_POSITION;
    float2 uv : UV;
    float4 normal : NORMAL;
    float4 world : WORLDMATRIX;
    

    //
    //  normal, tangent, bitangent to be in world space
    // 
    //  
    //  float4 position : SV_POSITION;
    //  float2 uv : UV;
    //  float3 normal : NORMAL;
    //  float3 worldPosition : WORLDPOSITION;
    //  float3 tangent : TANGENT
    //  float3 bitangent : BITANGENT
    //  
    //  
    //  
};


cbuffer cbChangesEveryFrame : register(b0)
{
    float4x4 BoneOffset[37];
};

cbuffer MatrixBuffer : register(b1)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

PSINPUT main(ANIMATED_LIT_INPUT input)
{
    PSINPUT output;
    float4 temp = float4(input.pos, 1.0f);
    float4 VertexOut = temp; 
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.x]) * input.blendWeights.x;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.y]) * input.blendWeights.y;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.z]) * input.blendWeights.z;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.w]) * input.blendWeights.w;

    

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(VertexOut, worldMatrix);
    output.world = float4(output.position.xyz, 1.0f);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    // Store the input color for the pixel shader to use.

    temp = float4(input.normal, 0.0f);
    VertexOut = temp;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.x]) * input.blendWeights.x;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.y]) * input.blendWeights.y;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.z]) * input.blendWeights.z;
    //VertexOut += mul(temp, BoneOffset[input.boneIndices.w]) * input.blendWeights.w;


    output.normal = mul(VertexOut, worldMatrix);
    output.normal = normalize(output.normal);

    output.uv = input.uv;
	return output;
}
