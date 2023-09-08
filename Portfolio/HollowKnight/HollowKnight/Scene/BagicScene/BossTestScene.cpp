#include "framework.h"
#include "BossTestScene.h"
#include "../../Object/HollowKnight/Player/Player.h"
#include "../../Object/HollowKnight/Monster/Boss.h"
#include "../../Object/HollowKnight/Monster/BossHead.h"

BossTestScene::BossTestScene()
{
	_player = make_shared<Player>();
	_boss = make_shared<Boss>();
	_boss->SetPlayer(_player);
	CAMERA->SetTarget(_player->GetTransform());
	_col = make_shared<RectCollider>(Vector2(20000, 300));
	_col->SetPosition(Vector2(0, -250));
	CAMERA->SetLeftBottom(Vector2(-100000, -130));
	CAMERA->SetRightTop(Vector2(100000, 100000));
	SOUND->Add("Main1", "Resource/Sound/BGM/S19 Crossroads Main.wav", true);
	SOUND->Add("Main2", "Resource/Sound/BGM/S19 Crossroads Bass.wav", true);
	SOUND->Play("Main2");
}

BossTestScene::~BossTestScene()
{
}

void BossTestScene::Update()
{
	_player->Update();
	_boss->Update();
	_col->Update();
	if (_col->Block(_player->GetCollider()))
		_player->SetIsJump(false);
	_col->Block(RECT(_boss->GetGravityCollider()));
	CAMERA->SetScale(Vector2(_scale, _scale));
	CAMERA->SetLeftBottom(Vector2(-100000, -130));
	CAMERA->SetRightTop(Vector2(100000, 100000));
	CAMERA->SetTarget(_player->GetTransform());
}

void BossTestScene::Render()
{
	_boss->Render();
	_player->Render();
	_col->Render();
}

void BossTestScene::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	_boss->PostRender();
	_player->PostRender();
}
