#include "framework.h"
#include "DungreedSceneTest.h"
#include "../Object/DungreedTest/Dun_Player.h"

DungreedSceneTest::DungreedSceneTest()
{
	_dun_player = make_shared<Dun_Player>();
}

DungreedSceneTest::~DungreedSceneTest()
{
}

void DungreedSceneTest::Update()
{
	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-500.0f, 0.0f) * DELTA_TIME;
		_dun_player->Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(500.0f, 0.0f) * DELTA_TIME;
		_dun_player->Move(movePos);
	}

	_dun_player->Update();
}

void DungreedSceneTest::Render()
{
	_dun_player->Render();
}

void DungreedSceneTest::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
}
