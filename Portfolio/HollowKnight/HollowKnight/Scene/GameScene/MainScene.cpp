#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_title = make_shared<MainString>(L"Resource/UI/Title.png", Vector2(1185.0f * 0.5f, 412.0f * 0.5f));
	_title->SetPosition(Vector2(0,200));
}

MainScene::~MainScene()
{
}

void MainScene::Update()
{
	_title->Update();
}

void MainScene::Render()
{
}

void MainScene::PostRender()
{
	_title->PostRender();
}

void MainScene::PreRender()
{
}
