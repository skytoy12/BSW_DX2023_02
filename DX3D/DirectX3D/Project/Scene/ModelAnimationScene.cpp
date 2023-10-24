#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	groot = new Groot();

	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap.png");

	//terrain->scale *= 2.0f;

	Camera::GetInstance()->SetTarget(groot);
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

	groot->translation.y = terrain->GetHeight(groot->GetGlobalPosition());
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
