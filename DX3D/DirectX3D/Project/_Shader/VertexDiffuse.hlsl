#include "Header.hlsli"

struct VertexOutput
{
    float4 pos    : SV_POSITION;
    float2 uv     : UV;
    float diffuse : DIFFUSE;
};

VertexOutput main(VertexTextureNormal input)
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.uv = input.uv;
    
    float3 L = normalize(-lightDirection);
    float3 N = normalize(mul(input.normal, (float3x3)world));
    
    output.diffuse = dot(N, L); // N dot L
    
    return output;
}