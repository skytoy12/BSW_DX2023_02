#include "framework.h"
#include "DungreedScene.h"
#include "../Object/Dungreed/Dungreed.h"
#include "../Object/Dungreed/DungreedBoss.h"

DungreedScene::DungreedScene()
{
	_dungreedPlayer = make_shared<Dungreed>();
	_boss = make_shared<DungreedBoss>();
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-500.0f, 0.0f) * DELTA_TIME;
		_dungreedPlayer->Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(500.0f, 0.0f) * DELTA_TIME;
		_dungreedPlayer->Move(movePos);
	}

	_dungreedPlayer->Update();
	_boss->Update();
}

void DungreedScene::Render()
{
	_dungreedPlayer->Render();
	_boss->Render();
}

void DungreedScene::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
}