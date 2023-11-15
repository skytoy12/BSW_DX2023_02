#include "Header.hlsli"

struct VertexOutPut // Geometry Input
{
    float3 pos     : POSITION0;
    float2 size    : SIZE;
    float3 viewPos : POSITION1;
    matrix view    : VIEW;
    matrix proj    : PROJECTION;
};

VertexOutPut main(VertexTexture input)
{
    VertexOutPut output;
    
    output.pos     = input.pos;
    output.size    = input.uv;
    output.viewPos = invView._41_42_43;
    output.view    = view;
    output.proj    = proj;
    
	return output;
}