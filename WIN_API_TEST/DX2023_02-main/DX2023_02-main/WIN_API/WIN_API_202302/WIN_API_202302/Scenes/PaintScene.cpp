#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
	_circle = make_shared<CircleCollider>(Vector2(300.0f, 300.0f), 50.0f);
	_rectMouse = make_shared<RectCollider>(Vector2(0.0f, 0.0f), Vector2(100, 150));

	_rect = make_shared<RectCollider>(Vector2(500.0f, 300.0f), Vector2(100, 150));
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
	Vector2 lerpResult = LERP(_rectMouse->GetCenter(), mousePos, 0.1f);
	_rectMouse->SetCenter(lerpResult);

	if (_circle->IsCollision(_rectMouse))
	{
		_circle->SetRed();
		_rectMouse->SetRed();
	}
	else
	{
		_circle->SetGreen();
		_rectMouse->SetGreen();
	}

	/*if (_rect->IsCollision(mousePos))
		_rect->SetRed();
	else
		_rect->SetGreen();*/

	if (_rect->IsCollision(_rectMouse))
	{
		_rect->SetRed();
		_rectMouse->SetRed();
	}
	else
	{
		_rect->SetGreen();
		_rectMouse->SetGreen();
	}
	_circle->Update();
	_rectMouse->Update();
	_rect->Update();
}

void PaintScene::Render(HDC hdc)
{
	_circle->Render(hdc);
	_rectMouse->Render(hdc);
	_rect->Render(hdc);
}
