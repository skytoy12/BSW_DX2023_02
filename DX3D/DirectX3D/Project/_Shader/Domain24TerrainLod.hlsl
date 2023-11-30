#include "Header.hlsli"

struct DomainOutput
{
    float4 pos : SV_POSITION;
    float2 uv  : UV;
};

struct HullOutput
{
    float4 pos : POSITION;
    float2 uv  : UV;
};

struct CHulOutput
{
    float   edgeTessFactor[4] : SV_TessFactor;
    float insideTessFactor[2] : SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 4

Texture2D heightMap : register(t10);
cbuffer heightBuffer : register(b10)
{
    float heightScale;
}

[domain("quad")]
DomainOutput main(CHulOutput input, float2 domain : SV_DomainLocation, const OutputPatch<HullOutput, NUM_CONTROL_POINTS> patch)
{
    DomainOutput output;

    float4 v1 = lerp(patch[0].pos, patch[1].pos, domain.x);
    float4 v2 = lerp(patch[2].pos, patch[3].pos, domain.x);
    float4 pos = lerp(v1, v2, domain.y);

    float2 uv1 = lerp(patch[0].uv, patch[1].uv, domain.x);
    float2 uv2 = lerp(patch[2].uv, patch[3].uv, domain.x);
    float2 texCoord = lerp(uv1, uv2, domain.y);
    
    pos.y = heightMap.SampleLevel(samp, texCoord, 0).r * heightScale;
    
    output.pos = float4(pos.xyz, 1.0f);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.uv = texCoord;
    
    return output;
}
