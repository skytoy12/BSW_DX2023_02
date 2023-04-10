#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render(HDC hdc);

	void SetPos(const Vector2& pos) { _circle->SetCenter(pos); }
	void Shoot(const Vector2& dir, float speed);

	bool IsActive() { return _isActive; }
	shared_ptr<CircleCollider> Circle() { return _circle;  }
	bool IsCollision(shared_ptr<CircleCollider> other)
	{
		return _circle->IsCollision(other);
	}

private:
	bool _isActive = false;
	float _speed = 30.0f;
	Vector2 _direction = Vector2(0.0f, 0.0f);

	shared_ptr<CircleCollider> _circle;
};

