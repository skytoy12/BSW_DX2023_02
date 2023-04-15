#pragma once
class Ball
{
public :
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);


	void SetPos(const Vector2& pos) { _arkanoidBall->SetCenter(pos); }
	void Shoot(const Vector2& dir, float speed);
	Vector2 GetBallCenter() { return _arkanoidBall->GetCenter(); }
	bool IsActive() { return _isActive; }
	shared_ptr<CircleCollider> GetBall() { return shared_ptr<CircleCollider>(_arkanoidBall); }
	void SetDir(const Vector2& dir) { _direction = dir; }
	Vector2 GetDir() { return _direction; }
	

private :
	shared_ptr<CircleCollider> _arkanoidBall;
	float _speed = 1.0f;
	Vector2 _direction = Vector2(1.0f, 1.0f);
	bool _isActive = false;
};

