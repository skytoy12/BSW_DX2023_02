#pragma once
class BrickImage
{
public:
	BrickImage(wstring path, Vector2 size);
	~BrickImage();

	void Update();
	void Render();

	void Save(string name, wstring flie);
	void Load(string name, wstring flie);

	
private:
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;
};



