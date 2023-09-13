#include "framework.h"
#include "TestScene.h"
#include "../../Object/HollowKnight/Player/Player.h"
#include "../../Object/HollowKnight/Monster/JumpMonster.h"
#include "../../Object/HollowKnight/Monster/FlyMonster.h"
#include "../../Object/HollowKnight/Monster/RushMonster.h"
TestScene::TestScene()
{
	_player = make_shared<Player>();
	_mon1 = make_shared<JumpMonster>();
	_mon1->SetPosition(Vector2(1800, 0));
	_mon1->SetPlayer(_player);
	_mon2 = make_shared<FlyMonster>(Vector2(-1800, 0));
	_mon2->SetPlayer(_player);
	_mon3 = make_shared<RushMonster>();
	_mon3->SetPosition(Vector2(800, 0));
	_mon3->SetPlayer(_player);
	//CAMERA->SetTarget(_player->GetTransform());
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
	_mon3->Update();
	_col->Update();
	if (_col->Block(_player->GetCollider()))
		_player->SetIsJump(false);
	_col->Block(RECT(_mon1->GetCollider()));
	_col->Block(RECT(_mon2->GetCollider()));
	_col->Block(RECT(_mon3->GetCollider()));
	CAMERA->SetScale(Vector2(_scale, _scale));
	CAMERA->SetLeftBottom(Vector2(-100000, -100000));
	CAMERA->SetRightTop(Vector2(100000, 100000));
	CAMERA->SetTarget(_player->GetTransform());
}

void TestScene::Render()
{
	_mon1->Render();
	_mon2->Render();
	_mon3->Render();
	_player->Render();
	_col->Render();
}

void TestScene::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	_player->PostRender();
	_mon1->PostRender();
	_mon3->PostRender();
}

void TestScene::PreRender()
{
}
