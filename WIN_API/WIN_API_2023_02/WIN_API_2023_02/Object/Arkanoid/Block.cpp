#include "framework.h"
#include "Block.h"

Block::Block()
{
	_rect = make_shared<RectCollider>(Vector2(0, 0), Vector2(90, 30));
}

Block::~Block()
{
}

void Block::Update()
{
	_rect->Update();
}

void Block::Render(HDC hdc)
{
	_rect->Render(hdc);
}


