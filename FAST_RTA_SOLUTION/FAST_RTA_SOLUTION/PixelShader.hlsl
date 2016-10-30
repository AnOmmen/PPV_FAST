struct PSINPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};



float4 main(PSINPUT input) : SV_TARGET
{
	return float4(0, 0, 1, 1);
}