#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	groot = new Groot();

	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap.png");

	//terrain->scale *= 2.0f;

	Camera::GetInstance()->SetTarget(groot);

	crossHair = new Quad();
	crossHair->GetMaterial()->SetDiffuseMap(L"UI/CrossHair.png");
	crossHair->GetMaterial()->SetShader(L"Texture");
	crossHair->scale *= 100.0f;
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete groot;
	delete terrain;
	delete crossHair;
}

void ModelAnimationScene::Update()
{
	groot->Update();
	terrain->Update();
	crossHair->Update();

	crossHair->translation.x = mousePos.x;
	crossHair->translation.y = WIN_HEIGHT - mousePos.y ;

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

	StateManager::GetInstance()->AlphaBegin();
	crossHair->Render();
	StateManager::GetInstance()->AlphaEnd();
}
