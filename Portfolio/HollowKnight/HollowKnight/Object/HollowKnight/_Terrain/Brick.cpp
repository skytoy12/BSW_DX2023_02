#include "framework.h"
#include "Brick.h"

Brick::Brick(wstring path, Vector2 size, Vector2 colSize)
{
	_transform = make_shared<Transform>();
	_col = make_shared<RectCollider>(colSize);
	_quad = make_shared<Quad>(path, size);

	_transform->SetParent(_col->GetTransform());
}

Brick::~Brick()
{
}

void Brick::Update()
{
	_transform->Update();
	_col->Update();

	BlockTarget();
}

void Brick::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_col->Render();
}

void Brick::BlockTarget()
{
	if (_target.expired() == true)
		return;
	if (_col->Block(_target.lock()->GetCollider()))
		_target.lock()->SetIsJump(false);
}
