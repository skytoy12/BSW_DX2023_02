#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	groot = new Groot();
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete groot;
}

void ModelAnimationScene::Update()
{
	groot->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	groot->Render();
}

void ModelAnimationScene::PostRender()
{
	groot->Debug();
}
