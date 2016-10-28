// Per-pixel color data passed through the pixel shader.
#include "LightCalc.hlsli"
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV0;
	float3 norm : NORM0;
	float3 world : WORLD0;
	float3 tan : TAN0;
	float4 biTan : BITAN0;
};


cbuffer LightConstantBuffer : register(b0)
{
	Light lights[3];
};

texture2D baseTexture : register(t0); // first texture
texture2D normalMap : register(t1); //normal map
SamplerState filters : register(s0); // filter 0 using CLAMP, filter 1 using WRAP

									 // A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 newNorm = normalMap.Sample(filters, input.uv);
	newNorm.xyz = (newNorm.xyz * 2.0f) - 1.0f;
	float3 temptan = normalize(input.tan);
	float3 tempnorm = normalize(input.norm);
	float4 tempbiTan = normalize(input.biTan);
	float3x3 TBN;
	TBN[0] = temptan.xyz;
	TBN[1] = tempbiTan.xyz;
	TBN[2] = tempnorm.xyz;
	newNorm.xyz = mul(newNorm.xyz, (float3x3)TBN);
	float4 baseColor = baseTexture.Sample(filters, input.uv); // get base color
	float3 dirLightColor = directionalCalc(lights[0], newNorm.xyz);
	float3 pointLightColor = pointCalc(lights[1], newNorm.xyz, input.world);
	float3 coneLightColor = coneCalc(lights[2], newNorm.xyz, input.world);
	float3 totalLightColor = saturate(dirLightColor + pointLightColor + coneLightColor);

	return baseColor * float4(totalLightColor, 1.0f);
	//return (baseColor * float4(saturate(dirLightColor), 1.0f));
}
