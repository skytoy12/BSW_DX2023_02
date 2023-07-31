#include "framework.h"
#include "Boss.h"

Boss::Boss()
{
	_col = make_shared<CircleCollider>(200);
	_transform->SetParent(_col->GetTransform());
}

Boss::~Boss()
{
}

void Boss::Update()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	Gravity(_col);
	_col->Update();
	_transform->Update();
}

void Boss::Render()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	_transform->SetBuffer(0);
	_col->Render();
}

void Boss::PostRender()
{
}

void Boss::Attack()
{
}

void Boss::SetLeft()
{
}

void Boss::SetRight()
{
}
