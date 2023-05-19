#include "framework.h"
#include "DungreedScene.h"
#include "../Object/Dungreed/DungreedBullet.h"

DungreedScene::DungreedScene()
{
	
	_player = make_shared<Dungreed>(L"Resource/Dungreed/Player.png", Vector2(1.0f, 1.0f));
	_bow = make_shared<Dungreed>(L"Resource/Dungreed/Bow.png", Vector2(1.0f, 1.0f), 30, Vector2(0.1f, 0.1f));


	_player->SetPosition(Vector2(100, 100));
	_bow->SetParent(_player->GetBow());
	
	_bow->SetPosition(Vector2(250, 10));
	
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	for (auto bullet : _bow->GetBullets())
	{
		if (bullet->GetPos().x > WIN_WIDTH || bullet->GetPos().y > WIN_HEIGHT)
		{
			bullet->SetIsActive(false);
			bullet->SetPosition(_bow->GetPos());
		}

	}
	_bow->SetAngle(3.8f);
	_player->SetbowAngle(mousePos.Angle());
	_player->Update();
	_bow->Update();
}

void DungreedScene::Render()
{
	_player->Render();
	_bow->Render();
}
