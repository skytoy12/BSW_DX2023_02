#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Wall.png", L"LandScape/Wall_specular.png", L"LandScape/Wall_normal.png", L"LandScape/Floor.png");
}

TerrainScene::~TerrainScene()
{
	delete terrain;
}


void TerrainScene::Update()
{
	terrain->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();
}

void TerrainScene::PostRender()
{
	terrain->GetMaterial()->PostRender();
}
