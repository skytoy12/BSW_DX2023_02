#pragma once
class ModelAnimation : public Transform
{
public:
	ModelAnimation(string name, wstring shaderFile = L"02ModelAnimation");
	~ModelAnimation();

	void Update();
	void Render();

	void ReadClip(string file, UINT clipIndex = 0);

	void CreateTexture();

private :
	void CreateClipTransform(UINT index);

private:
	ModelReader* reader;

	vector<ModelClip*> clips;

	string name;

	FrameBuffer* frameBuffer;

	ClipTransform* clipTransform;
	ClipTransform* nodeTransform;

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;
};