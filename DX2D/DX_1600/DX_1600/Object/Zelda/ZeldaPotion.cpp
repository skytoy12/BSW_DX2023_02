#include "framework.h"
#include "ZeldaPotion.h"

ZeldaPotion::ZeldaPotion(Vector2 curframe, Vector2 pos)
{
	Vector2 size = ADD_SRV(L"Resource/Item_11x5.png")->GetImageSize();
	size.x /= 11;
	size.y /= 5;

	_sprite = make_shared<Sprite>(L"Resource/Item_11x5.png", Vector2(11, 5), size);
	_sprite->SetCurFrame(curframe);

	_collider = make_shared<CircleCollider>((size.x + size.y) / 2 * 0.8);
	_transform = make_shared<Transform>();

	_transform->SetParent(_collider->GetTransform());
	_collider->SetPosition(pos);
}

ZeldaPotion::~ZeldaPotion()
{
}

void ZeldaPotion::Collider_Update()
{
	if (_isActive == false)
		return;
	_collider->Update();
}

void ZeldaPotion::Update()
{
	if (_isActive == false)
		return;
	_sprite->Update();
	_transform->Update();
}

void ZeldaPotion::Render()
{
	if (_isActive == false)
		return;
	_transform->SetBuffer(0);
	_sprite->Render();
	_collider->Render();
}
