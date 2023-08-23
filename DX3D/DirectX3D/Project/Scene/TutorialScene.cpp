#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	cube1 = new Cube({0.0f, 0.2f, 0.5f, 1.0f});
	cube2 = new Cube({0.0f, 0.5f, 0.2f, 1.0f});

	cube2->translation.x = 3;

	cube2->SetParent(cube1);
}

TutorialScene::~TutorialScene()
{
	delete cube1;
	delete cube2;
}

void TutorialScene::Update()
{
	cube1->Update();
	cube2->Update();

	cube1->rotation.y += 0.0001f;
}

void TutorialScene::PreRender()
{

}

void TutorialScene::Render()
{
	cube1->Render();
	cube2->Render();
}

void TutorialScene::PostRender()
{
	cube1->Debug();
	cube2->Debug();
}
