#include "LightCalc.hlsli"




struct PSINPUT
{
	float4 position : SV_POSITION;
	float2 uv : COLOR;
    float4 normal : NORMAL;
    float4 world : WORLDMATRIX;
    float3 bitan : BITAN;
    float3 tan : TAN;
};

texture2D basetexture : register (t0);
texture2D normaltexture : register(t1);
texture2D speculartexture : register(t2);


SamplerState filter;



cbuffer LightBuffer
{
    LIGHT light[3];
}

cbuffer CameraPos
{
    float4 cameraPos;
}

float4 main(PSINPUT input) : SV_TARGET
{

	float3 newNormal = (normaltexture.Sample(filter, input.uv)* 2.0f) - 1.0f;
    float3x3 tbn = { normalize(input.tan), normalize(input.bitan), normalize(input.normal.xyz) };
    newNormal = mul(newNormal, tbn);
	normalize(newNormal);


    float4 baseColor = basetexture.Sample(filter, input.uv);
    float3 color1, color2, color3;
    color1 = DirLight(light[0].pos, float4(newNormal, 0), light[0].color).xyz;
    color2 = PointLight(light[1].pos, input.world, float4(newNormal, 0), light[1].color, light[1].r).xyz;
    color3 = SpotLight(input.world.xyz, light[2].normal.xyz, light[2].r.z, float3(newNormal.xyz), light[2]);
     
    float3 finalcolor = color1 + color2 + color3;
    float3 color4 = SpecularCalc(cameraPos.xyz, input.world.xyz, newNormal.xyz, finalcolor.xyz, speculartexture.Sample(filter, input.uv).x, light[1].pos.xyz);
    
    finalcolor += color4;


    finalcolor = saturate(finalcolor);
    finalcolor = finalcolor * baseColor.xyz;

    return float4(finalcolor.xyz, baseColor.w);
   // return float4(1, 0, 0, 1);
    //return float4(input.normal.xyz, 1.0);
}