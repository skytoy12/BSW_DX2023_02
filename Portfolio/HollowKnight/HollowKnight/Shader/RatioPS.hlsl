
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer RatioBuffer : register(b0)
{
	float max;
	float cur;
	float padding[2];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : UV;
};



float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = map.Sample(samp, input.uv);
	float ratio = (float)cur / (float)max;

	if (ratio > 1)
		ratio = 1;
	if (input.uv.x > ratio)
	{
		color.w = 0.5f;
		return color;
	}


	return color;
}