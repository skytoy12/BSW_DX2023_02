#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
	_circle = make_shared<CircleCollider>(Vector2(300.0f, 300.0f), 50.0f);
	_rectengle = make_shared<RectengleCollider>(100.0f, 100.0f, 300.0f, 400.0f);
}

PaintScene::~PaintScene()
{
}

void PaintScene::Updata()
{
	if (GetAsyncKeyState('A'))
	{
		_rectengle->MoveRecHR(-1);
	}
	if (GetAsyncKeyState('D'))
	{
		_rectengle->MoveRecHR(1);
	}

	if (GetAsyncKeyState('W'))
	{
		_rectengle->MoveRecVT(-1);
	}
	if (GetAsyncKeyState('S'))
	{
		_rectengle->MoveRecVT(1);
	}
	_rectengle->Updata();
}

void PaintScene::Render(HDC hdc)
{
	_circle->Render(hdc);
	_rectengle->Render(hdc);
}
