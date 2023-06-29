#pragma once
class Shader
{
public :
	Shader() {}
	virtual ~Shader() {}

	virtual void Set() abstract;

protected :
	wstring file;
	ComPtr<ID3DBlob> _blob;
};

