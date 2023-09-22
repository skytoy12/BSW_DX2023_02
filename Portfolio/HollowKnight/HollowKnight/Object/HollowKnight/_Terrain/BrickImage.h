#pragma once
class BrickImage
{
public:
	BrickImage(wstring path, Vector2 size);
	~BrickImage();

	void Update();
	void Render();

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }
	Vector2 GetScale() { return _transform->GetScale(); }
	wstring Getpath() { return _quad->GetPath(); }

	void SetPosition(Vector2 value);
	void SetScale(Vector2 value) { _transform->SetScale(value); }
	void SetSRV(wstring file) { _quad->SetSRV(file); }
	void ReturnPos() { _transform->SetPosition(_oldPos); }

	bool _isActive = true;
private:
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;

	Vector2 _oldPos;
};



