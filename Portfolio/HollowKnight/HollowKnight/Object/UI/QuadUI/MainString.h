#pragma once
class MainString
{
public :
	MainString(wstring path, Vector2 size);
	~MainString();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	Vector2 GetPos() { return _transform->GetWorldPosition(); }

	shared_ptr<Collider> GetCollider() { return _collider; }

private :
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

};

