struct LIGHT
{
    float4 pos;
    float4 color;
    float4 normal;
    float4 r;
};


float4 DirLight(float4 lightdir, float4 surfacenormal, float4 color)
{
    float lightratio = saturate(dot((-1 * lightdir), surfacenormal));
    return (lightratio * color);
}

float4 PointLight(float4 lightpos, float4 surfacepos, float4 surfacenormal, float4 color, float4 radius)
{
    float4 lightdir = normalize(lightpos - surfacepos);
    float attenuation = 1.0f - saturate(length(lightpos.xyz - surfacepos.xyz) / radius.x);
    float lightratio = saturate(dot(lightdir, surfacenormal));
    return (lightratio * color * attenuation);
}

float3 SpotLight(float3 surfacepos, float3 conedir,
	float coneratio, float3 surfacenormal, LIGHT light)
{
    float3 lightdir = normalize(light.pos.xyz - surfacepos);
    float surfaceratio = saturate(dot(-1 * lightdir, conedir));
    float a1, a2;
    a1 = 1.0f - saturate(length(light.pos.xyz - surfacepos) / light.r.x);
    a2 = 1.0f - saturate((light.r.y - surfaceratio) / (light.r.y - light.r.z));
    float spotfactor = a1 * a2;
    float lightratio = saturate(dot(lightdir.xyz, surfacenormal));
    return (spotfactor * lightratio * light.color);
   // return float3(0, 0, 1);
}
