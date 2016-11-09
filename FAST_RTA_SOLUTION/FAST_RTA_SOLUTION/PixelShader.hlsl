#include "LightCalc.hlsli"




struct PSINPUT
{
	float4 position : SV_POSITION;
	float2 uv : COLOR;
    float4 normal : NORMAL;
    float4 world : WORLDMATRIX;
};

texture2D basetexture;

SamplerState filter;



cbuffer LightBuffer
{
    LIGHT light[3];
}


float4 main(PSINPUT input) : SV_TARGET
{
    float4 baseColor = basetexture.Sample(filter, input.uv);
    float3 color1, color2, color3;
    color1 = DirLight(light[0].pos, input.normal, light[0].color).xyz;
    color2 = PointLight(light[1].pos, input.world, input.normal, light[1].color, light[1].r).xyz;
    color3 = SpotLight(input.world.xyz, light[2].normal.xyz, light[2].r.z, float3(input.normal.xyz), light[2]);
    float3 finalcolor = color1 + color2 + color3;
     finalcolor = saturate(finalcolor);
     finalcolor = finalcolor * baseColor.xyz;
    return float4(finalcolor.xyz, baseColor.w);
   // return float4(1, 0, 0, 1);
    //return float4(input.normal.xyz, 1.0);
}