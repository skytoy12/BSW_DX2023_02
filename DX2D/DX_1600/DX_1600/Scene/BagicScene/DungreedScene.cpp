#include "framework.h"
#include "DungreedScene.h"
#include "../../Object/Dungreed/DungreedBoss.h"
#include "../../Object/Dungreed/Dun_Player_Advanced.h"

DungreedScene::DungreedScene()
{
	_dungreedPlayer = make_shared<Dun_Player_Advanced>();
	_dungreedPlayer->SetPosition(CENTER);

	_floor = make_shared<RectCollider>(Vector2((float)WIN_WIDTH, 100.0f));
	_floor->SetPosition(Vector2(CENTER.x, 50.0f));

	_boss = make_shared<DungreedBoss>();
	_boss->SetPosition(Vector2(WIN_WIDTH - 100.0f, WIN_HEIGHT - 100.0f));
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Collider_Update()
{
	_dungreedPlayer->Collider_Update();
	_floor->Update();
	_boss->Collider_Update();
}

void DungreedScene::Update()
{
	_dungreedPlayer->Update();
	_boss->Update();

	_dungreedPlayer->SetFalling(!_floor->Block(_dungreedPlayer->GetCollider()));

	if (_boss->_isActive)
	{
		if (_dungreedPlayer->isCollision_Bullets(_boss->GetCollider()))
		{
			_boss->ReduceHP(1);
		}
	}

}

void DungreedScene::Render()
{
	_dungreedPlayer->Render();
	_floor->Render();
	_boss->Render();

}

void DungreedScene::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
	ImGui::Text("boss HP : %d", _boss->GetHP());
	ImGui::Text("bullet.x : %d", _dungreedPlayer->GetBullets()[0]->GetCollider()->GetTransform()->GetWorldPosition().x);
	ImGui::Text("bullet.y : %d", _dungreedPlayer->GetBullets()[0]->GetCollider()->GetTransform()->GetWorldPosition().y);
}