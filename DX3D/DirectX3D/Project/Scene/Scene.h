#pragma once

struct Vertex
{
    Vertex(float x, float y, float z)
    {
        pos = XMFLOAT3(x, y, z);
    }

    XMFLOAT3 pos;
};

struct VertexColor
{
    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        :pos(pos), color(color)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct WVP
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
};



class Scene
{
public :

	virtual ~Scene() = default;

	virtual void Update() = 0;

	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

protected :
    WVP wvp;

    vector<VertexColor> vertices;
    vector<UINT>    indices;

    ID3D11Device* device;         // 무언가를 만들 때 사용, CPU를 다루는 객체 
    ID3D11DeviceContext* deviceContext;  // 무언가를 그릴 때 사용, GPU를 다루는 객체(RENDER, HDC)

    IDXGISwapChain* swapChain;         // 더블버퍼링을 구현하는 객체
    ID3D11RenderTargetView* renderTargetView;  // 백버퍼를 관리하는 객체

    //////////////////////////////////////////////////////////////////////////

    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;

    ID3D11InputLayout* inputLayout;

    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;

    ID3D11Buffer* constBuffer;

    UINT stride = 0;
    UINT offset = 0;
};
