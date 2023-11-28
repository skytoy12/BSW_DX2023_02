#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObjects();

	//reflection = new Reflection(floor);
	//refraction = new Refraction(L"Landscape/Wave.dds");

	sky = new SkyBox(L"LandScape/Snow_ENV.dds");

	//floor->GetMaterial()->SetShader(L"20Refraction");

	water = new Water(L"Landscape/Wave.dds");
	shadow = new Shadow(10000, 10000);
	//water->translation.y += 10.0f;

	LightBuffer::LightData& light = Environment::GetInstance()->GetLightBuffer()->data.lights[0];

	light.type = 1;
	light.position = { 0, 100, -50 };
	light.range = 2000.0f;
}

WaterScene::~WaterScene()
{
	delete floor;
	delete groot;
	delete bunny;
	delete sphere;

	delete sky;

	delete water;
	delete shadow;
	//delete reflection;
	//delete refraction;
}

void WaterScene::Update()
{
	floor->Update();
	groot->Update();
	bunny->Update();
	sphere->Update();

	//water->Update();

	//reflection->Update();
	//refraction->Update();
}

void WaterScene::PreRender()
{
	//reflection->SetPreRender();
	//refraction->SetPreRender();
	//water->SetReflection();

	//sky->Render();
	//groot->Render();
	//bunny->Render();
	//sphere->Render();

	//water->SetRefraction();

	//sky->Render();
	//groot->Render();
	//bunny->Render();
	//sphere->Render();


	shadow->SetPreRender();


	groot->Render();
	bunny->Render();
	sphere->Render();
}

void WaterScene::Render()
{
	sky->Render();

	//reflection->SetRender();
	//refraction->SetRender();
	//water->Render();
	shadow->SetRender();

	floor->Render();
	groot->Render();
	bunny->Render();
	sphere->Render();
}

void WaterScene::PostRender()
{
	//reflection->PostRender();
	//refraction->PostRender();
	//refraction->Debug();
	//water->Debug();

	//floor->Debug();
	shadow->PostRender();
}

void WaterScene::CreateObjects()
{
	wstring shaderFile = L"09Light";
	floor = new Quad();
	floor->SetLabel("Floor");

	floor->rotation.x = XM_PIDIV2;
	floor->translation.y = 1.0f;
	floor->scale *= 100.0f;
	floor->GetMaterial()->SetShader(L"22Shadow");

	groot = new Groot();
	groot->GetReader()->SetShader(shaderFile);

	bunny = new Model("StanfordBunny");
	bunny->SetLabel("Bunny");
	bunny->scale *= 0.05f;
	bunny->translation = { -30, 12, 0 };
	bunny->GetReader()->SetShader(shaderFile);

	sphere = new Sphere();
	sphere->scale *= 5.0f;
	sphere->translation = { 30, 20, 0 };
	sphere->GetMaterial()->SetDiffuseMap(L"LandScape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetNormalMap(L"LandScape/FieldStone_NM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"LandScape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetShader(shaderFile);
	sphere->SetLabel("Sphere");
}
