#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	soldier = new Soldier();

	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap256.png");
}

TestScene::~TestScene()
{
	delete soldier;
	delete terrain;
}

void TestScene::Update()
{
	soldier->Update();
	terrain->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	soldier->Render();
	terrain->Render();
}

void TestScene::PostRender()
{
	soldier->PostRender();
	terrain->Debug();
}
