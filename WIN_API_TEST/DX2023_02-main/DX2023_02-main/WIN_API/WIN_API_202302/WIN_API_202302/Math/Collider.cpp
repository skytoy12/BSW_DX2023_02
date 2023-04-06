#include "framework.h"
#include "Collider.h"

Collider::Collider(Vector2 center)
: _center(center)
, _type(Collider::ColliderType::NONE)
{
	HPEN green = CreatePen(PS_SOLID, 3, GREEN);
	HPEN red = CreatePen(PS_SOLID, 3, RED);
	HPEN blue = CreatePen(PS_SOLID, 3, BLUE);
	HPEN black = CreatePen(PS_SOLID, 3, BLACK);
	_pens.push_back(green);
	_pens.push_back(red);
	_pens.push_back(blue);
	_pens.push_back(black);
}

Collider::~Collider()
{
	for (auto& pen : _pens)
	{
		DeleteObject(pen);
	}
}

void Collider::MoveCenter(const Vector2& value)
{
	_center += value;
}

void Collider::SetCenter(const Vector2& value)
{
	_center = value;
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
	// col�� Rect�ϱ� Circle
	switch (col->_type)
	{
	case Collider::ColliderType::NONE:
	{
		// �߸��� collider �����Դϴ�.
		return false;
		break;
	}

	case Collider::ColliderType::CIRCLE:
	{
		return IsCollision(dynamic_pointer_cast<CircleCollider>(col));
		break;
	}

	case Collider::ColliderType::RECT:
	{
		return IsCollision(dynamic_pointer_cast<RectCollider>(col));
		break;
	}

	default:
		break;
	}

    return false;
}