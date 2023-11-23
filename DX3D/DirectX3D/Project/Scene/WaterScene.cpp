#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObjects();

	reflection = new Reflection(floor);

	sky = new SkyBox(L"LandScape/Snow_ENV.dds");

	floor->GetMaterial()->SetShader(L"19Reflection");
}

WaterScene::~WaterScene()
{
	delete floor;
	delete groot;
	delete bunny;
	delete sphere;

	delete sky;
}

void WaterScene::Update()
{
	floor->Update();
	groot->Update();
	bunny->Update();
	sphere->Update();

	reflection->Update();
}

void WaterScene::PreRender()
{
	reflection->SetPreRender();

	sky->Render();

	//floor->Render();
	groot->Render();
	bunny->Render();
	sphere->Render();
}

void WaterScene::Render()
{
	sky->Render();

	reflection->SetRender();

	floor->Render();
	groot->Render();
	bunny->Render();
	sphere->Render();
}

void WaterScene::PostRender()
{
	reflection->PostRender();
}

void WaterScene::CreateObjects()
{
	floor = new Quad();
	floor->SetLabel("Floor");

	floor->rotation.x = XM_PIDIV2;
	floor->translation.y = 1.0f;
	floor->scale *= 100.0f;
	floor->GetMaterial()->SetShader(L"09Light");

	groot = new Groot();
	groot->GetReader()->SetShader(L"09Light");

	bunny = new Model("StanfordBunny");
	bunny->SetLabel("Bunny");
	bunny->scale *= 0.05f;
	bunny->translation = { -30, 12, 0 };
	bunny->GetReader()->SetShader(L"09Light");

	sphere = new Sphere();
	sphere->scale *= 5.0f;
	sphere->translation = { 30, 20, 0 };
	sphere->GetMaterial()->SetDiffuseMap(L"LandScape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetNormalMap(L"LandScape/FieldStone_NM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"LandScape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetShader(L"09Light");
	sphere->SetLabel("Sphere");
}
