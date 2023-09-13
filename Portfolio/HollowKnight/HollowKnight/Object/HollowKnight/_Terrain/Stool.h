#pragma once
class Stool
{
public:
	Stool(wstring path, Vector2 size, Vector2 colSize);
	~Stool();

	void Update();
	void Render();

	void SetTarget(shared_ptr<Player> target) { _target = target; }

	shared_ptr<Transform> GetTransform() { return _transform; }

	void BlockTarget();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private:
	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _col;
	shared_ptr<Quad> _quad;

	weak_ptr<Player> _target;
};



