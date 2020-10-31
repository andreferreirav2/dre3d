float4 vsmain(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

float4 psmain(float4 pos : SV_POSITION) : SV_Target
{
	return float4(245.0f / 255, 180.0f / 255, 97.0f / 255, 1.0f);
}
