#include "framework.h"
#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
	_canonEnemy = make_shared<canonEnemy>(Vector2(1000, WIN_HEIGHT * 0.5f));
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
	_canonEnemy->Update();
	_canonEnemy->Damaged(_cannon);
	
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	if (_canonEnemy->IsAlive() == true)
	{
		_canonEnemy->Render(hdc);
	}
	
}
