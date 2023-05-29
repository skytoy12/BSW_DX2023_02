#include "framework.h"
#include "DungreedBoss.h"

DungreedBoss::DungreedBoss()
{
	_quad = make_shared<Quad>(L"Resource/Dungreed/Boss.png");
	_quad->GetTransform()->SetPosition(Vector2(1000, 500));
	_quad->GetTransform()->SetScale(Vector2(0.4f, 0.4f));
}

DungreedBoss::~DungreedBoss()
{
}

void DungreedBoss::Update()
{
	if (_isActive == true)
		_quad->Update();
}

void DungreedBoss::Render()
{
	if (_isActive == true)
		_quad->Render();
}

void DungreedBoss::ReduceHP(int damage)
{
	if (damage > _hp)
		return;
	_hp -= damage;
}

