#pragma once
class Shader
{
protected:
	virtual ~Shader();

public:

	static class  VertexShader*  GetVS(wstring file);
	static class   PixelShader*  GetPS(wstring file);
	static class ComputeShader*  GetCS(wstring file);
	static class GeometryShader* GetGS(wstring file);
	static class HullShader*     GetHS(wstring file);
	static class DomainShader*   GetDS(wstring file);

	static void Delete();

	virtual void SetShader() = 0;

	wstring GetPath() { return path; }

protected:
	ID3DBlob* blob;

	static map<wstring, Shader*> shaders;

	wstring path;
};

