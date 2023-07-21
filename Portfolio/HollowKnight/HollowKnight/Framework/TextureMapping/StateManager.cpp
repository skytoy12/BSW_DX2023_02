#include "framework.h"
#include "StateManager.h"

StateManager* StateManager::_instance = nullptr;

StateManager::StateManager()
{
	_sampler = make_shared<SamplerState>();

	_alpha = make_shared<BlendState>();
	_alpha->Alpha();

	_additive = make_shared<BlendState>();
	_additive->Additive();

	_blendState = make_shared<BlendState>();

	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE; //BackFace Culling
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rasterizerState);

	DC->RSSetState(rasterizerState);
}

StateManager::~StateManager()
{
}
