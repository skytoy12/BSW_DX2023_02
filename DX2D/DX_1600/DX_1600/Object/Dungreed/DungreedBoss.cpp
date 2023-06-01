#include "framework.h"
#include "DungreedBoss.h"

DungreedBoss::DungreedBoss()
{
	_quad = make_shared<Quad>(L"Resource/Dungreed/Boss.png");
	_collider = make_shared<CircleCollider>(_quad->GetImageSize().x);
	_collider->SetScale(0.5f);
	_quad->GetTransform()->SetParent(_collider->GetTransform());
}

DungreedBoss::~DungreedBoss()
{
}

void DungreedBoss::Collider_Update()
{
	if (_isActive == true)
		_collider->Update();
}

void DungreedBoss::Update()
{
	if (_isActive == true)
		_quad->Update();
}

void DungreedBoss::Render()
{
	if (_isActive == true)
	{
		_quad->Render();
		_collider->Render();
	}
		
}

void DungreedBoss::ReduceHP(int damage)
{
	if (damage > _hp || !_isActive)
		return;
	_hp -= damage;
	if (_hp <= 0)
		_isActive = false;
}

