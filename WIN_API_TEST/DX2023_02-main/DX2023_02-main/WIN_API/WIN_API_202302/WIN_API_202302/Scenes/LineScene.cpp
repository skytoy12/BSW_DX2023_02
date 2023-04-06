#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	
	_lineFloor = make_shared<Line>(Vector2(0,500), Vector2(1000,500)); // ��������, 3
	_lineMouse = make_shared<Line>(Vector2(50, 250), Vector2(50, 250)); // �Ķ�����, 3
	_lineShadow = make_shared <Line>(Vector2(50, 450), Vector2(60, 450)); // ������, 3
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	Vector2 result = _lineMouse->_end - _lineMouse->_start;
	_lineMouse->_end = mousePos;
	_lineShadow->_end = Vector2 (result.Dot(Vector2(1, 0)), 450);
	
	_lineFloor->Update();
	_lineMouse->Update();
	_lineShadow->Update();
}

void LineScene::Render(HDC hdc)
{
	HPEN red = CreatePen(PS_SOLID, 3, RED);
	HPEN blue = CreatePen(PS_SOLID, 3, BLUE);
	HPEN black = CreatePen(PS_SOLID, 3, BLACK);
	SelectObject(hdc, black);
	_lineFloor->Render(hdc);
	SelectObject(hdc, blue);
	_lineMouse->Render(hdc);
	SelectObject(hdc, red);
	_lineShadow->Render(hdc);
	DeleteObject(red);
	DeleteObject(black);
	DeleteObject(blue);
}
