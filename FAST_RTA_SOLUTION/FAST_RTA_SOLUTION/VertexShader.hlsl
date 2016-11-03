cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};
struct VSINPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
    float4 normal : NORMAL;
};

struct PSINPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 world : WORLDMATRIX;
};

PSINPUT main(VSINPUT input)
{
	PSINPUT output;
    // Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
    output.world = float4(input.position.xyz, 1.0f);
    // Calculate the position of the vertex against the world, view, and projection matrices.
	output.position.w = 1;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
    // Store the input color for the pixel shader to use.
	output.color = input.color;
    output.normal = mul(input.normal, worldMatrix);
    output.normal = normalize(output.normal);
	return output;
}