#include "Framework.h"
#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(vector<UINT>& indices)
{
    D3D11_BUFFER_DESC bufferDesc = {};

    bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
    bufferDesc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 용도를 물어보는 것
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA data;

    data.pSysMem = indices.data(); // vector의 data함수는 주소값을 반환하는 함수

    DEVICE->CreateBuffer(&bufferDesc, &data, &indexBuffer);
}

IndexBuffer::~IndexBuffer()
{
    indexBuffer->Release();
}

void IndexBuffer::IASetBuffer()
{
    DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
