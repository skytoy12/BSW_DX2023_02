#include "Framework.h"
#include "Environment.h"
Environment::Environment()
{
    CreateViewport();
    CreatePerspective();
}

Environment::~Environment()
{
    delete projBuffer;
}

void Environment::CreateViewport()
{
	D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width    = WIN_WIDTH;
    viewPort.Height   = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort);
}

void Environment::CreatePerspective()
{
    projBuffer = new MatrixBuffer();

    XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

    projBuffer->SetData(projection);

    projBuffer->SetVSBuffer(2);
}
