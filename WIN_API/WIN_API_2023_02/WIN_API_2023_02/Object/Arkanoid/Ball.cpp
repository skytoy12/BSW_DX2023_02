#include "framework.h"
#include "Ball.h"

Ball::Ball()
{
	_arkanoidBall = make_shared<CircleCollider>(Vector2(0,0), 5);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (_isActive == false)
		return;
	_arkanoidBall->MoveCenter(_direction * _speed);
	Vector2 xa = _arkanoidBall->GetCenter() + Vector2(5, 0);
	Vector2 xb = _arkanoidBall->GetCenter() + Vector2(-5, 0);
	Vector2 ya = _arkanoidBall->GetCenter() + Vector2(0, -5);
	Vector2 yb = _arkanoidBall->GetCenter() + Vector2(0, 5);
	
	if (xa.x > ((WIN_WIDTH / 2) + 400) || xb.x < ((WIN_WIDTH / 2) - 400))
		_direction.x *= -1;
	if (ya.y < 0.0f)
		_direction.y *= -1;
	if (yb.y > WIN_HEIGHT)
		_isActive = false;

	_arkanoidBall->Update();
}

void Ball::Render(HDC hdc)
{
	if (_isActive == false)
		return;
	_arkanoidBall->Render(hdc);		
}

void Ball::Shoot(const Vector2& dir, float speed)
{
	_isActive = true;
	_direction = dir;
	_speed = speed;
}
