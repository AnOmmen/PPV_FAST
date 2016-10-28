// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float2 uv : UV0;
	float3 norm : NORM0;
	float4 tan : TAN0;
	//float3 world : WORLD0;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV0;
	float3 norm : NORM0;
	float3 world : WORLD0;
	float3 tan : TAN0;
	float4 biTan : BITAN0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);
	float4 norm = float4(input.norm, 0.0f);
	float4 tan = float4(input.tan.xyz, 0.0f);
	float4 biTan;
	// Transform the vertex position into projected space.
	pos = mul(pos, model);
	output.world = pos;
	tan = mul(tan, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	biTan.xyz = cross(float4(input.norm, 0.0f), float4(input.tan.xyz, 0.0f));
	biTan.w = 0.0f;
	output.pos = pos;
	output.norm = mul(norm, model);
	output.uv = input.uv;
	output.tan = tan;
	output.biTan = mul(biTan, model);
	// Pass the color through without modification.

	return output;
}