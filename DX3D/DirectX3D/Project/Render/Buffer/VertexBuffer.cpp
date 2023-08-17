#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    vertexBuffer->Release();
}

void VertexBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetPrimitiveTopology(type); // vertex들의 연결 방식
    DC->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}
