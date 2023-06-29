#include "framework.h"
#include "TestScene.h"
#include "../../Object/HollowKnight/Player.h"
TestScene::TestScene()
{
	_player = make_shared<Player>();
	CAMERA->SetTarget(_player->GetTransform());
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_player->Update();
}

void TestScene::Render()
{
	_player->Render();
}
