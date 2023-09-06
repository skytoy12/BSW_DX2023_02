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
	void SetSpecularMap(wstring file);

	MaterialBuffer* GetBuffer() { return buffer; }

	void PostRender();

private:
	VertexShader* vertexShader = nullptr;
	 PixelShader* pixelShader = nullptr;

	 Texture* diffuseMap = nullptr;
	 Texture* specularMap = nullptr;

	 MaterialBuffer* buffer = nullptr;
};


