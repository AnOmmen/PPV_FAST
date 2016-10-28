struct Light
{
	//w holds type of light
	//0 = directional
	//1 = point
	//2 = cone
	float4 pos;
	float4 norm;
	float4 color;
	//x = lightradius y = innerconeratio z = outerconeratio
	float4 ratio;

};

float3 directionalCalc(Light p_light, float3 surfNorm)
{
	float Lratio;
	Lratio = saturate(dot(-1 * (p_light.norm.xyz), surfNorm));
	float3 Result = Lratio * p_light.color.xyz;
	return Result;
}

float3 pointCalc(Light p_light, float3 surfNorm, float3 surfPos)
{
	float3 lightDir = normalize(p_light.pos.xyz - surfPos);
	float Lratio = saturate(dot(lightDir, surfNorm));

	float Attenuation = 1.0 - saturate(length(p_light.pos.xyz - surfPos) / p_light.ratio.x);
	Attenuation *= Attenuation;
	float3 Result = Lratio * p_light.color.xyz * Attenuation;
	return Result;
}

float3 coneCalc(Light p_light, float3 surfNorm, float3 surfPos)
{
	float3 lightDir = normalize(p_light.pos.xyz - surfPos);
	float surfRatio = saturate(dot((-1 * lightDir), p_light.norm.xyz));
	float Attenuation = 1.0 - saturate((p_light.ratio.y - surfRatio) / (p_light.ratio.y - p_light.ratio.z));
	float falloffRadius = 1.0 - saturate(length(p_light.pos.xyz - surfPos) / p_light.ratio.x);

	float Lratio = saturate(dot(lightDir, surfNorm));
	float3 Result = Attenuation * falloffRadius * Lratio * p_light.color.xyz;
	return Result;
}