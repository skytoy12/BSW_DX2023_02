#include "Header.hlsli"

struct VertexOutput
{
    float4 pos           : SV_POSITION;
    float4 reflectionPos : POSITION;
};

Texture2D reflectionMap : register(t10);

float4 main(VertexOutput input) : SV_TARGET
{
    float2 uv;
    
    uv.x = +input.reflectionPos.x / input.reflectionPos.w * 0.5f + 0.5f;
    uv.y = -input.reflectionPos.y / input.reflectionPos.w * 0.5f + 0.5f;
    
    return reflectionMap.Sample(samp, uv);
}