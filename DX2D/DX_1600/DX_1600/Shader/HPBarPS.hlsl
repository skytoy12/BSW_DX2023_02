
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer HPBarBuffer : register(b0)
{
	float maxHP;
	float curHP;
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
	input.uv.x = input.uv.x * (curHP / maxHP);
	float4 color = map.Sample(samp, input.uv);

	return color;
}