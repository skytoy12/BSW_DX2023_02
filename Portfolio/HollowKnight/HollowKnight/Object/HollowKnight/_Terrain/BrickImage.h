#pragma once
class BrickImage
{
public:
	BrickImage(wstring path, Vector2 size);
	~BrickImage();

	void Update();
	void Render();

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }
	Vector2 GetScale() {};
	wstring Getpath() {};
	void SetPosition(Vector2 value) { _transform->SetPosition(value); }

	bool _isActive = true;
private:
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;
};



