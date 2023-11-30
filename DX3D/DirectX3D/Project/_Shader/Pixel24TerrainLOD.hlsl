#include "Header.hlsli"

struct DomainOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

float4 main(DomainOutput input) : SV_TARGET
{
    return diffusemap.Sample(samp, input.uv);
}