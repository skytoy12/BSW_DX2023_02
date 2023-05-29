#include "framework.h"
#include "DungreedBossScene.h"

DungreedBossScene::DungreedBossScene()
{
	_player = make_shared<Dungreed>();
	_boss = make_shared<DungreedBoss>();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<CircleCollider> bulletCollider = make_shared<CircleCollider>(100.0f);
		bulletCollider->SetParent(_player->GetBullets()[i]->GetTransform());
		bulletCollider->SetIsActive(_player->GetBullets()[i]->_isActive);
		_bulletColliders.push_back(bulletCollider);
	}

	_player->SetPosition(Vector2(0.0f, 0.0f));

	_floorCollider = make_shared<RectCollider>(Vector2(1600, 100));
	_playerCollider = make_shared<CircleCollider>(50.0f);
	_bossCollider = make_shared<CircleCollider>(100.0f);

	_floorCollider->GetTransform()->SetPosition(Vector2(CENTER - Vector2(0.0f, 350.0f)));
	_playerCollider->GetTransform()->SetPosition(_player->GetPos() + Vector2(100.0f, 200.0f));
	_bossCollider->GetTransform()->SetPosition(_boss->GetPos());

	_player->SetPratent(_playerCollider->GetTransform());
}

DungreedBossScene::~DungreedBossScene()
{
}

void DungreedBossScene::Update()
{
	_player->Update();
	_boss->Update();

	_floorCollider->Update();
	_playerCollider->Update();
	_bossCollider->Update();

	for (int i = 0; i < 30; i++)
	{
		_bulletColliders[i]->SetIsActive(_player->GetBullets()[i]->_isActive);
		if (_bulletColliders[i]->GetISActive() == true)
			_bulletColliders[i]->Update();
	}


	_playerCollider->GetTransform()->AddVector2(Vector2(0.0f, -GRAVITY * _speed));

	_floorCollider->Block(_playerCollider);

	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-500.0f, 0.0f) * DELTA_TIME;
		_playerCollider->GetTransform()->AddVector2(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(500.0f, 0.0f) * DELTA_TIME;
		_playerCollider->GetTransform()->AddVector2(movePos);
	}

	if (KEY_PRESS(' '))
	{
		Vector2 movePos = Vector2(0.0f, 1000.0f) * DELTA_TIME;
		_playerCollider->GetTransform()->AddVector2(movePos);
	}
}

void DungreedBossScene::Render()
{
	_player->Render();
	_boss->Render();

	_floorCollider->Render();
	_playerCollider->Render();
	_bossCollider->Render();

	for (int i = 0; i < 30; i++)
	{
		_bulletColliders[i]->SetIsActive(_player->GetBullets()[i]->_isActive);
		if (_bulletColliders[i]->GetISActive() == true)
			_bulletColliders[i]->Render();
	}
}

void DungreedBossScene::PostRender()
{
	ImGui::Text("Boss HP : %d", _boss->GetHP());
}
