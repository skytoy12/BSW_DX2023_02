#pragma once
class SamplerState
{
public :
	SamplerState();
	~SamplerState();

	void Set(int slot);

private :
	ComPtr<ID3D11SamplerState> samplerState;
};

