float4 vsmain(float4 position : POSITION) : SV_POSITION
{
	position.x = position.x * 1.1f;
	return position;
}