#include "framework.h"
#include "Bar.h"

Bar::Bar()
{
	_arkanoidBar = make_shared<RectCollider>(Vector2(WIN_WIDTH / 2, WIN_HEIGHT - 100), Vector2(100, 10));
	_ball = make_shared<Ball>();
	_brush = CreateSolidBrush(RGB(150, 150, 255));
}

Bar::~Bar()
{
	DeleteObject(_brush);
}

void Bar::Update()
{

	if (_arkanoidBar->IsCollision(_ball->GetBallCenter() + Vector2(0,5)))
		_ball->SetDir((_ball->GetBallCenter() - _arkanoidBar->GetCenter()).NormalVector2());
	Move();
	Fire();
	_arkanoidBar->Update();
	_ball->Update();
}

void Bar::Render(HDC hdc)
{
	SelectObject(hdc, _brush);
	_arkanoidBar->Render(hdc);
	_ball->Render(hdc);
}

void Bar::Move()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (_arkanoidBar->GetCenter().x - 50 > (WIN_WIDTH / 2) - 400)
			_arkanoidBar->MoveCenter(Vector2(-1.0f * _speed, 0.0f));
	}

	if(GetAsyncKeyState(VK_RIGHT))
		if(_arkanoidBar->GetCenter().x + 50 < (WIN_WIDTH / 2) + 400)
			_arkanoidBar->MoveCenter(Vector2(1.0f * _speed, 0.0f));
}

void Bar::Fire()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if (_ball->IsActive() == false)
		{
			_ball->SetPos(_arkanoidBar->GetCenter() + Vector2(0, -10));
			_ball->Shoot((_ball->GetBallCenter() - _arkanoidBar->GetCenter()).NormalVector2(), 7.0f);
		}
	}
	
}
