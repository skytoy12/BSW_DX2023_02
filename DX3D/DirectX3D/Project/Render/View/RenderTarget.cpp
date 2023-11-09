#include "Framework.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(UINT width, UINT height)
	:width(width), height(height)
{
	CreateRTVTexture();
	CreateRTV();
	CreateSRV();
}

RenderTarget::~RenderTarget()
{
	rtvTexture->Release();
	       rtv->Release();
	       srv->Release();
}

void RenderTarget::Set(DepthStencil* depthStencil, Vector4 clearColor)
{
	DC->OMSetRenderTargets(1, &rtv, depthStencil->GetDSV());

	DC->ClearRenderTargetView(rtv, (float*)&clearColor);
	depthStencil->Clear();

	Environment::GetInstance()->SetEnvironment();
	Environment::GetInstance()->SetViewport(width, height);
}

void RenderTarget::CreateRTVTexture()
{
	D3D11_TEXTURE2D_DESC Desc;

	Desc.Width              = width;
	Desc.Height             = height;
	Desc.MipLevels          = 1;
	Desc.ArraySize          = 1;
	Desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.SampleDesc.Count   = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage              = D3D11_USAGE_DEFAULT;
	Desc.BindFlags          = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	Desc.CPUAccessFlags     = 0;
	Desc.MiscFlags          = 0;

	DEVICE->CreateTexture2D(&Desc, nullptr, &rtvTexture);
}

void RenderTarget::CreateRTV()
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	rtvDesc.Format        = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	DEVICE->CreateRenderTargetView(rtvTexture, &rtvDesc, &rtv);
}

void RenderTarget::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format                   = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension            = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2DArray.MipLevels = 1;

	DEVICE->CreateShaderResourceView(rtvTexture, &srvDesc, &srv);
}
