#pragma once
class GeometryBuffer
{
	enum RenderTargets
	{
		DIFFUSE,
		NORMAL,
		SPECULAR,
		EMVIENT,
		EMISSIVE,
		SIZE
	};

public:
	GeometryBuffer();
	~GeometryBuffer();

	void SetMultiRenderTarget();
	void PostRender();
	void SetSRVs();

private:

	DepthStencil* depthStencil;
	RenderTarget* rtvs[SIZE];

	class Quad* quads[SIZE + 1];
	ID3D11ShaderResourceView* srvs[SIZE + 1];
};



