#include "framework.h"
#include "Stool.h"

Stool::Stool(wstring path, Vector2 size, Vector2 colSize)
{
	_transform = make_shared<Transform>();
	_col = make_shared<RectCollider>(colSize);
	_quad = make_shared<Quad>(path, size);

	_transform->SetParent(_col->GetTransform());
}

Stool::~Stool()
{
}

void Stool::Update()
{
	_transform->Update();
	_col->Update();

	BlockTarget();
}

void Stool::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_col->Render();
}

void Stool::BlockTarget()
{
	if (_target.expired() == true)
		return;
	if(_col->Block(_target.lock()->GetCollider()))
		_target.lock()->SetIsJump(false);
}
