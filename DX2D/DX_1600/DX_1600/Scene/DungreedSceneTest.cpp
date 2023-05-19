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
	_dun_player->Update();
}

void DungreedSceneTest::Render()
{
	_dun_player->Render();
}
