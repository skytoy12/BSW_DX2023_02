#include "framework.h"
#include "TestScene.h"
#include "../../Object/HollowKnight/Player/Player.h"
#include "../../Object/HollowKnight/Monster/JumpMonster.h"
#include "../../Object/HollowKnight/Monster/RushMonster.h"
#include "../../Object/HollowKnight/Monster/FlyMonster.h"
TestScene::TestScene()
{
	_player = make_shared<Player>();
	_mon1 = make_shared<JumpMonster>();
	_mon1->SetPosition(Vector2(800, 0));
	_mon1->SetTarget(_player->GetTransform());
	_mon2 = make_shared<FlyMonster>(Vector2(-800, 0));
	_mon2->SetTarget(_player->GetTransform());

	CAMERA->SetTarget(_player->GetTransform());
	_col = make_shared<RectCollider>(Vector2(20000, 30));
	_col->SetPosition(Vector2(0, -250));
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_player->Update();
	_mon1->Update();
	_mon2->Update();
	_col->Update();
	if (_col->Block(_player->GetCollider()))
		_player->SetIsJump(false);
	_col->Block(_mon1->GetCollider());
	_col->Block(_mon2->GetCollider());
	CAMERA->SetScale(Vector2(_scale, _scale));
}

void TestScene::Render()
{
	_player->Render();
	_mon1->Render();
	_mon2->Render();
	_col->Render();
}

void TestScene::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	_mon1->PostRender();
	_mon2->PostRender();
}
