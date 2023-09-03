#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
	sphere = new Sphere({ 0.0f, 0.2f, 0.5f, 1.0f }, 50.0f);
}

SphereScene::~SphereScene()
{
}

void SphereScene::Update()
{
	sphere->Update();
}

void SphereScene::PreRender()
{
}

void SphereScene::Render()
{
	sphere->Render();
}

void SphereScene::PostRender()
{
}
