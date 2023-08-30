#include "Framework.h"
#include "Environment.h"
Environment::Environment()
{
    CreateViewport();
    CreatePerspective();
}

Environment::~Environment()
{
    delete viewBuffer;
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
    viewBuffer = new MatrixBuffer();
    projBuffer = new MatrixBuffer();

    XMVECTOR   eyePos = XMVectorSet(+0.0f, +10.0f, -5.0f, +1.0f);
    XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +0.0f);
    XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

    viewBuffer->SetData(view);


    XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

    projBuffer->SetData(projection);

    viewBuffer->SetVSBuffer(1);
    projBuffer->SetVSBuffer(2);
}
