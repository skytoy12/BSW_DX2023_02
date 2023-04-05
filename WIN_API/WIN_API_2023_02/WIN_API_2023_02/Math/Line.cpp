#include "framework.h"
#include "Line.h"

void Line::Updata()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, _start.x, _start.y, nullptr);
	LineTo(hdc, _end.x, _end.y);
}
