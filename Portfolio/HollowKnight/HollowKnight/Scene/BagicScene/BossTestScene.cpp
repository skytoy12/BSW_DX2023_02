#include "framework.h"
#include "BossTestScene.h"
#include "../../Object/HollowKnight/Player/Player.h"
#include "../../Object/HollowKnight/Monster/Boss.h"

BossTestScene::BossTestScene()
{
	_player = make_shared<Player>();
	_boss = make_shared<Boss>();
	_boss->SetTarget(_player->GetTransform());
	CAMERA->SetTarget(_player->GetTransform());
	_col = make_shared<RectCollider>(Vector2(20000, 30));
	_col->SetPosition(Vector2(0, -250));
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
	_col->Block(_boss->GetCollider());
	CAMERA->SetScale(Vector2(_scale, _scale));
}

void BossTestScene::Render()
{
	_player->Render();
	_boss->Render();
	_col->Render();
}

void BossTestScene::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
}
