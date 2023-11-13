#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	groot = new Groot();

	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap.png");

	//terrain->scale *= 2.0f;

	//CAMERA->SetTarget(groot);

	crossHair = new Quad();
	crossHair->GetMaterial()->SetDiffuseMap(L"UI/CrossHair.png");
	crossHair->GetMaterial()->SetShader(L"Texture");
	crossHair->scale *= 100.0f;

	sky = new SkyBox(L"LandScape/Test2.dds");
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete groot;
	delete terrain;
	delete crossHair;
	delete sky;
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
	sky->Render();
	groot->Render();
	terrain->Render();
}

void ModelAnimationScene::PostRender()
{
	groot->PostRender();
	crossHair->Render();
	sky->PostRender();
}
