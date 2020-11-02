float4 vsmain(float4 position : POSITION) : SV_POSITION
{
	if (position.y > 0.0f)
 {

		position.x = position.x + 0.2f;
}
	return position;
}