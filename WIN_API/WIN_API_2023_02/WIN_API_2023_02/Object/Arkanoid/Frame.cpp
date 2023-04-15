#include "framework.h"
#include "Frame.h"

Frame::Frame()
{
	_arkanoidFrame = make_shared<RectCollider>(Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2(800, WIN_HEIGHT));
	_brush = CreateSolidBrush(GREY);
}

Frame::~Frame()
{
	DeleteObject(_brush);
}

void Frame::Update()
{
	_arkanoidFrame->Update();
}

void Frame::Render(HDC hdc)
{
	SelectObject(hdc, _brush);
	_arkanoidFrame->Render(hdc);
}
