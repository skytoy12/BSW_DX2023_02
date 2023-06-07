#include "framework.h"
#include "ActionScene.h"
#include "../../Object/Zelda/ZeldaAction.h"
#include "../../Object/Zelda/ZeldaPotion.h"

ActionScene::ActionScene()
{
	_zelda = make_shared<ZeldaAction>();
	_potion = make_shared<ZeldaPotion>(Vector2(4 , 0));
	_potion2 = make_shared<ZeldaPotion>(Vector2(5 , 0));

	_potion2->SetPos(Vector2(300, 300));
}

ActionScene::~ActionScene()
{
}

void ActionScene::Collider_Update()
{
	_zelda->Collider_Update();
	_potion->Collider_Update();
	_potion2->Collider_Update();
}

void ActionScene::Update()
{
	_zelda->Update();
	_potion->Update();
	_potion2->Update();
}

void ActionScene::Render()
{
	_zelda->Render();
	_potion->Render();
	_potion2->Render();
}

void ActionScene::PostRender()
{
	_zelda->PostRender();
}