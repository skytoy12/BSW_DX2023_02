#include "Header.hlsli"

VertexTexture main(VertexTexture input)
{
    input.pos = mul(input.pos, world);
    
	return input;
}