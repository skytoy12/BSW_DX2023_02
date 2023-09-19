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

private:
	vector<shared_ptr<BrickImage>> _brickImages;
};



