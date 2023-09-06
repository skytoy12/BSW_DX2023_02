#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"HeightMap/HeightMap.png");
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
