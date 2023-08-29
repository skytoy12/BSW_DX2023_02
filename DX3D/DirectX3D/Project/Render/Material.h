#pragma once
class Material
{
public:
	Material();
	Material(wstring file);
	~Material();

	void SetVertexShader(wstring file);
	void SetPixelShader(wstring file);

	void SetShader(wstring file);

	void SetMaterial();

	void SetDuffuseMap(wstring file);
private:
	VertexShader* vertexShader = nullptr;
	 PixelShader* pixelShader = nullptr;
	 Texture* diffuseMap = nullptr;
};


