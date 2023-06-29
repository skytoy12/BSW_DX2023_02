#include "framework.h"
#include "ActionScene.h"
#include "../../Object/Zelda/ZeldaAction.h"
#include "../../Object/Zelda/ZeldaPotion.h"

ActionScene::ActionScene()
{
	_zelda = make_shared<ZeldaAction>();
}

ActionScene::~ActionScene()
{
}


void ActionScene::Update()
{
	_zelda->Update();
	_zelda->Collider_Update();
}

void ActionScene::Render()
{
	_zelda->Render();
}

void ActionScene::PostRender()
{
	_zelda->PostRender();
}