#pragma once
class VectorBrick
{
public:
	VectorBrick();
	~VectorBrick();

	void Update();
	void Render();

	void Save(string name, wstring flie);
	void Load(string name, wstring flie);

	void SetName(string name) { _name = name; }
	void SetSaveFile(wstring save) { _savefile = save; }

	shared_ptr<BrickImage> GetBrickImage(int number) { return _brickImages[number]; }

private:
	vector<shared_ptr<BrickImage>> _brickImages;

	string _name;
	wstring _savefile;
};



