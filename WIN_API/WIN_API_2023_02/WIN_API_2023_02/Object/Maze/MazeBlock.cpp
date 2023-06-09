#include "framework.h"
#include "MazeBlock.h"

MazeBlock::MazeBlock()
{
	_rect = make_shared<RectCollider>(Vector2(0, 0), Vector2(14, 14));

	HBRUSH none = CreateSolidBrush(WHITE);
	HBRUSH able = CreateSolidBrush(GREEN);
	HBRUSH disable = CreateSolidBrush(RED);
	HBRUSH start = CreateSolidBrush(CYAN);
	HBRUSH end = CreateSolidBrush(BLUE);
	HBRUSH player = CreateSolidBrush(WHITE);
	HBRUSH foot_Print = CreateSolidBrush(GREY);
	HBRUSH visited = CreateSolidBrush(RGB(120, 50, 50));


	_brushes.reserve(9);
	_brushes.push_back(none);
	_brushes.push_back(able);
	_brushes.push_back(disable);
	_brushes.push_back(start);
	_brushes.push_back(end);
	_brushes.push_back(player);
	_brushes.push_back(foot_Print);
	_brushes.push_back(visited);
}

MazeBlock::~MazeBlock()
{
	for (auto& brush : _brushes)
		DeleteObject(brush);
}

void MazeBlock::Update()
{
	_rect->Update();
}

void MazeBlock::Render(HDC hdc)
{
	SelectObject(hdc, _brushes[static_cast<UINT>(_type)]);
	_rect->Render(hdc);
}
