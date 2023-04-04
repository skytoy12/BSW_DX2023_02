#include "framework.h"
#include "RectengleCollider.h"

RectengleCollider::RectengleCollider(float left, float top, float right, float bottom)
	: _left(left)
	, _top(top)
	, _right(right)
	, _bottom(bottom)
{
}

RectengleCollider::~RectengleCollider()
{
}

void RectengleCollider::Updata()
{
}

void RectengleCollider::Render(HDC hdc)
{
	Rectangle(hdc, _left, _top, _right, _bottom);
}

void RectengleCollider::MoveRecVT(const float& value)
{
	_top += value;
	_bottom += value;
}

void RectengleCollider::MoveRecHR(const float& value)
{
	_left += value;
	_right += value;
}
