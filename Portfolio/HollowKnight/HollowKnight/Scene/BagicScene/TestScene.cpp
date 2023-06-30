#include "framework.h"
#include "TestScene.h"
#include "../../Object/HollowKnight/Player.h"
TestScene::TestScene()
{
	_player = make_shared<Player>();
	CAMERA->SetTarget(_player->GetTransform());
	_col = make_shared<RectCollider>(Vector2(2000, 30));
	_col->SetPosition(Vector2(0, -250));
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_player->Update();
	_col->Update();
	_col->Block(_player->GetCollider());
	CAMERA->SetScale(Vector2(_scale, _scale));
}

void TestScene::Render()
{
	_player->Render();
	_col->Render();
}

void TestScene::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
}
