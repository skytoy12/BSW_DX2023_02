
Texture2D map : register(t0);
SamplerState samp : register(s0);


struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer AlphaBuffer : register(b5)
{
	float alpha;
}



float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = map.Sample(samp, input.uv);
	color.w = alpha;

	return color;
}