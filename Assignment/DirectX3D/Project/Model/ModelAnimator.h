#pragma once
class ModelAnimator : public Transform
{
public:
	ModelAnimator(string name, wstring shaderFile = L"02ModelAnimation");
	~ModelAnimator();

	void Update();
	void Render();
	void Debug();

	void ReadClip(string file, UINT clipIndex = 0);

	void PlayClip(UINT clipIndex, float speed = 1.0f, float takeTime = 0.2f);

	void CreateTexture();

	void UpdateFrame();

	Matrix GetTransformByBone(UINT boneIndex);
	Matrix GetTransformByNode(UINT nodeIndex);

private:
	void CreateClipTransform(UINT index);

protected:
	ModelReader* reader;

	vector<ModelClip*> clips;

	string name;

	FrameBuffer* frameBuffer;

	ClipTransform* clipTransform;
	ClipTransform* nodeTransform;

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;
};