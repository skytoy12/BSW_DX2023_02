#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	groot = new Groot();

	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap.png");
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete groot;
	delete terrain;
}

void ModelAnimationScene::Update()
{
	groot->Update();
	terrain->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	groot->Render();
	terrain->Render();
}

void ModelAnimationScene::PostRender()
{
	groot->Debug();
}
