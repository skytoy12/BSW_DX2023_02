#pragma once
class BackGround
{
public:
	BackGround(wstring path, Vector2 size);
	~BackGround();

	void Update();
	void Render();

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }
	Vector2 GetScale() { return _transform->GetScale(); }
	wstring Getpath() { return _quad->GetPath(); }

	void SetPosition(Vector2 value) { _transform->SetPosition(value); }
	void SetScale(Vector2 value) { _transform->SetScale(value); }
	void SetSRV(wstring file) { _quad->SetSRV(file); }

	Vector2 GetImageSize() { return _quad->GetImageSize(); }


	bool _isActive = true;

private:
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;
	shared_ptr<FilterBuffer> _filterBuffer;
};



