#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_lineFloor = make_shared<Line>(Vector2(0, 500), Vector2(1000, 330)); // 검은색선, 3
	_lineMouse = make_shared<Line>(Vector2(50, 250), Vector2(50, 250));  // 파란색선, 3
	_lineShadow = make_shared<Line>(Vector2(50, 450), Vector2(60, 450)); // 빨간색선, 3
}

LineScene::~LineScene()
{
}

void LineScene::Updata()
{
	_lineMouse->_end = mousePos;
	Vector2 line_mouseVec = _lineMouse->GetVector2();
	Vector2 line_FloorVec = _lineFloor->GetVector2();
	Vector2 floor_Normal = line_FloorVec.NormalVector2();
	float shadowLength = line_mouseVec.Dot(floor_Normal);
	_lineShadow->_end = _lineShadow->_start + floor_Normal * shadowLength;

	_lineFloor->Updata();
	_lineMouse->Updata();
	_lineShadow->Updata();
}

void LineScene::Render(HDC hdc)
{
	_lineFloor->Render(hdc);
	_lineMouse->Render(hdc);
	_lineShadow->Render(hdc);
}
