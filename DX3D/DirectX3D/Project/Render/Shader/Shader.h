#pragma once
class Shader
{
protected:
	Shader();
	virtual ~Shader();

public:

	static class VertexShader* GetVS(wstring file);
	static class  PixelShader* GetPS(wstring file);

	static void Delete();

	virtual void SetShader() = 0;

protected:
	ID3DBlob* blob;

	static unordered_map<wstring, Shader*> shaders;
};

