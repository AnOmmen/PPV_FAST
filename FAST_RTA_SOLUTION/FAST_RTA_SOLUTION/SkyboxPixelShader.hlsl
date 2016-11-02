


// Per-pixel color data passed through the pixel shader.
struct PSINPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 world : WORLDMATRIX;
};


TextureCube basetexture : register(t0);

SamplerState filter : register(s0);




 
// A pass-through function for the (interpolated) color data.
float4 main(PSINPUT input) : SV_TARGET
{
    float4 baseColor = basetexture.Sample(filter, input.color);

    return baseColor;
}
