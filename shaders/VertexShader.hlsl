struct VS_INPUT
{
	float4 position: POSITION;
	float4 position1: POSITION1;
	float3 color : COLOR;
	float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 world;
	row_major float4x4 view;
	row_major float4x4 proj;
	unsigned int time;
}

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//lerp(input.position, input.position1, (sin(time / 500.f) + 1.0f) / 2);
	// local -> world space
	output.position = mul(input.position, world);
	// world -> view space
	output.position = mul(output.position, view);
	// view -> screen space
	output.position = mul(output.position, proj);

	output.color = input.color;
	output.color1 = input.color1;

	/*
	if (output.position.y > 0.0f)
	{
		output.position.x = output.position.x + 0.2f;
	}
	*/

	return output;
}
