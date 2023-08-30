#pragma once
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState();

private:
	ID3D11RasterizerState* rasterizerState = nullptr;

	D3D11_RASTERIZER_DESC desc = {};
};


