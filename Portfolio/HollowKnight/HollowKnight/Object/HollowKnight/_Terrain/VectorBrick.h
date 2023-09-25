#pragma once
class VectorBrick
{
public:
	VectorBrick();
	~VectorBrick();

	void Update();
	void Render();

	void PostRender();

	void SavePS(string name, wstring file);
	void LoadPS(string name, wstring file);

	void SaveWString(wstring file);
	void LoadWString(wstring file);

	string ToString(wstring str);
	wstring ToWString(string str);

	void SetName(string name) { _name = name; }
	void SetSaveFile(wstring save) { _savefile = save; }

	void SetImageSaveName(wstring name) { _image += name; }

	void SelectImage();

	shared_ptr<BrickImage> GetBrickImage(int number) { return _brickImages[number]; }

private:
	vector<shared_ptr<BrickImage>> _brickImages;

	float _brickScaleX = 1.0f;
	float _brickScaleY = 1.0f;

	float _brickPosX = 0.0f;
	float _brickPosY = 0.0f;


	int _curNum = 99;
	int _brickNumber = 0;

	wstring _imageType = L"Ceil/";
	int _imagenumber = 0;

	wstring _select = L"";

	string _name;
	wstring _savefile;

	wstring _image = L"Info/";
};



