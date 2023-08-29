
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int isRight;
	int padding;
}

cbuffer MonsterBuffer : register(b1)
{
	int value1;
	float value2;
	float value3;
	float value4;
}



struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};



float4 PS(PixelInput input) : SV_TARGET
{
	if (isRight == 0)
		input.uv.x = 1 - input.uv.x;

	input.uv.x = (startPos.x / imageSize.x) + (size.x / imageSize.x) * input.uv.x;
	input.uv.y = (startPos.y / imageSize.y) + (size.y / imageSize.y) * input.uv.y;

	float4 color = map.Sample(samp, input.uv);
	if (color.x > 0.9f && color.y < 0.1f && color.z < 0.1f)
		return float4(0, 0, 0, 0);

	[branch]
	if (value1 == 0)
	{
		return color;
	}
	else if (value1 == 1)
	{
		color.x += value2;
		color.y += value3;
		color.z += value4;

		return  color;
	}

	return color;
}