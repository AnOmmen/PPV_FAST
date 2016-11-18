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
    return (spotfactor * lightratio * light.color).xyz;
   // return float3(0, 0, 1);
}

float3 SpecularCalc(float3 CamWorldPos, float3 SurfacePos, 
float3 normal, float3 lightcolor, float specularIntensity, float3 lightpos)
{
  float3 toCamera = normalize(SurfacePos - CamWorldPos);
   float specScale = 30 * pow(saturate(dot(reflect( (SurfacePos - lightpos), normal), toCamera)), .7);
  float3 finalspeccolor = .1 * specScale * lightcolor;
  return (finalspeccolor * specularIntensity);
 //float3 toCamera = normalize(CamWorldPos - SurfacePos);
 //float3 toLight = normalize(lightpos - SurfacePos);
 //float3 reflection = reflect(normalize(toLight * -1), normalize(normal.xyz));
 //float ratio = dot(normalize(reflection), normalize(toCamera));
 //ratio = saturate(ratio);
 //ratio = pow(ratio, 32);
 //float3 returnval = ratio * lightcolor;
 //return returnval * specularIntensity;
}