#include "Framework.h"
#include "TerrainLODScene.h"

TerrainLODScene::TerrainLODScene()
{
	terrain = new TerrainLOD(L"HeightMap/HeightMap.png");
}

TerrainLODScene::~TerrainLODScene()
{
	delete terrain;
}

void TerrainLODScene::Update()
{
	terrain->Update();
}

void TerrainLODScene::PreRender()
{
}

void TerrainLODScene::Render()
{
	terrain->Render();
}

void TerrainLODScene::PostRender()
{
	terrain->Debug();
}
