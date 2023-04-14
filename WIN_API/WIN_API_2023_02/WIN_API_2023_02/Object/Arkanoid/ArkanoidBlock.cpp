#include "framework.h"
#include "ArkanoidBlock.h"

ArkanoidBlock::ArkanoidBlock()
{
	_rect = make_shared<RectCollider>(Vector2(0, 0), Vector2(90, 30));
}

ArkanoidBlock::~ArkanoidBlock()
{
}

void ArkanoidBlock::Update()
{
	_rect->Update();
}

void ArkanoidBlock::Render(HDC hdc)
{
	_rect->Render(hdc);
}
