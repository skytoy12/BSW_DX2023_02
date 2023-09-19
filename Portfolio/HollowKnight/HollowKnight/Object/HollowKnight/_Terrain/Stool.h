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
	shared_ptr<RectCollider> GetCollider() { return _col; }
	Vector2 GetSize() { return Vector2(_width, _height); }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
	void SetScale(Vector2 scale);

	void BlockTarget();
	void BlockR(shared_ptr<RectCollider> col);
	void BlockC(shared_ptr<CircleCollider> col);


private:
	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _jumpCol;
	shared_ptr<Quad> _quad;

	weak_ptr<Player> _target;

	float _width;
	float _height;
};



