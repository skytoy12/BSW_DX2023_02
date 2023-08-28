#pragma once

class Quad : public Transform
{
public:
	Quad(Vector2 size = { 1, 1 });
	~Quad();

	void Render();

private:
	Material* material = nullptr;
	Mesh*     mesh     = nullptr;

	vector<VertexTexture> vertices;
	vector<UINT>           indices;

	ID3D11ShaderResourceView*    srv = nullptr;
	ID3D11SamplerState* samplerState = nullptr;

	MatrixBuffer* worldBuffer = nullptr;
};