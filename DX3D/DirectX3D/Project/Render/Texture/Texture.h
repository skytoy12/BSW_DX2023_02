#pragma once
class Texture
{

private :
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Get(wstring file);
	static void Delete();

	void PSSetShaderResources(UINT slot);

private:
	ID3D11ShaderResourceView* srv = nullptr;
	ScratchImage image;

	static map<wstring, Texture*> textures;
};

