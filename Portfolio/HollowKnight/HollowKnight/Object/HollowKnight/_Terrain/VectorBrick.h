#pragma once
class VectorBrick
{
public:
	VectorBrick();
	~VectorBrick();

	void Update();
	void Render();

	void PostRender();

	void SavePS(string name, wstring flie);
	void LoadPS(string name, wstring flie);

	void SaveWString(string name, wstring flie);
	void LoadWString(string name, wstring flie);

	string ToString(wstring str);
	wstring ToWString(string str);

	void SetName(string name) { _name = name; }
	void SetSaveFile(wstring save) { _savefile = save; }

	shared_ptr<BrickImage> GetBrickImage(int number) { return _brickImages[number]; }

private:
	vector<shared_ptr<BrickImage>> _brickImages;

	float _brickScaleX = 1.0f;
	float _brickScaleY = 1.0f;

	int _curNum = 0;
	int _brickNumber = 0;
	wstring _imageType = L"Ceil/";

	string _name;
	wstring _savefile;
};



