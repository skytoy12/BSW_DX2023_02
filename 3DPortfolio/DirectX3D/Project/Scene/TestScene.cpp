#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	soldier = new Soldier();
}

TestScene::~TestScene()
{
	delete soldier;
}

void TestScene::Update()
{
	soldier->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	soldier->Render();
}

void TestScene::PostRender()
{
	soldier->PostRender();
}
