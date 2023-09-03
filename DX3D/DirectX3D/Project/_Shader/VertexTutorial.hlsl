#include "Header.hlsli"

struct VertexColorNormal
{
    float4 pos   : POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float diffuse : DIFFUSE;
};

VertexOutput main(VertexColorNormal input)
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.color = input.color;
    
    float3 L = normalize(-lightDirection);
    float3 N = normalize(mul(input.normal, (float3x3) world));
    
    output.diffuse = dot(N, L); // N dot L
	return output;
}