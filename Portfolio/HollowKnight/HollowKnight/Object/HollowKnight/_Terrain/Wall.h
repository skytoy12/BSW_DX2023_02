#pragma once
class Wall
{
public:
	Wall(Vector2 colSize);
	~Wall();

	void Update();
	void Render();

	void BlockTarget();

	void BlockR(shared_ptr<RectCollider> col);
	void BlockC(shared_ptr<CircleCollider> col);

	void SetTarget(shared_ptr<Player> target) { _target = target; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
	void SetScale(Vector2 scale);

private:
	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _jumpCol;
	weak_ptr<Player> _target;

	float _width;
	float _height;
};

