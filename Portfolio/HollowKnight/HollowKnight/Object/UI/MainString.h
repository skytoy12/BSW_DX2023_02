#pragma once
class MainString
{
public :
	MainString(wstring path, Vector2 size);
	~MainString();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	void SetEvent(CallBack callBack) { _event = callBack; }

	void SetTarget(shared_ptr<Collider> target) { _target = target; }

	shared_ptr<Collider> GetCollider() { return _collider; }

private :
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	weak_ptr<Collider> _target;

	CallBack _event;
};

