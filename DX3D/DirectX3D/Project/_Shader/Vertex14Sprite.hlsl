#include "Header.hlsli"

struct VertexOutPut // Geometry Input
{
    float3 pos     : POSITION0;
    float2 size    : SIZE;
    matrix invView : INVVIEW;
    matrix view    : VIEW;
    matrix proj    : PROJECTION;
};

VertexOutPut main(VertexTexture input)
{
    VertexOutPut output;
    
    output.pos     = input.pos;
    output.size    = input.uv;
    output.invView = invView;
    output.view    = view;
    output.proj    = proj;
    
    return output;
}