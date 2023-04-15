#include "framework.h"
#include "ArkanoidBlock.h"

ArkanoidBlock::ArkanoidBlock()
{
	_rect = make_shared<RectCollider>(Vector2(0, 0), Vector2(50, 20));

	

	HBRUSH none = CreateSolidBrush(WHITE);
	HBRUSH nomalBlock = CreateSolidBrush(RGB(0, 128, 128));
	HBRUSH hardBlock = CreateSolidBrush(RGB(178,34,34));
	HBRUSH itemBlock = CreateSolidBrush(RED);

	_brushes.reserve(4);
	_brushes.push_back(none);
	_brushes.push_back(nomalBlock);
	_brushes.push_back(hardBlock);
	_brushes.push_back(itemBlock);
}

ArkanoidBlock::~ArkanoidBlock()
{
	for (auto& brush : _brushes)
		DeleteObject(brush);
}

void ArkanoidBlock::Update()
{
	if (_isAlive == false)
		return;
	_rect->Update();
	
}

void ArkanoidBlock::Render(HDC hdc)
{
	if (_isAlive == false)
		return;
	SelectObject(hdc, _brushes[static_cast<UINT>(_type)]);
	_rect->Render(hdc);
}
