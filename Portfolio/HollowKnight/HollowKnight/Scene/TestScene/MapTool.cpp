#include "framework.h"
#include "MapTool.h"

MapTool::MapTool()
{
	_player = make_shared<Player>();

	_stool1 = make_shared<Stool>(L"Resource/Stool/stool1.png", Vector2(169, 199), Vector2(135, 120));
	_stool1->SetPosition(Vector2(200, 500));
	_stool1->GetTransform()->SetPosition(Vector2(0, -20));

	_stool2 = make_shared<Stool>(L"Resource/Stool/stool2.png", Vector2(131, 106), Vector2(110, 50));
	_stool2->GetTransform()->SetPosition(Vector2(0, -15));

	CAMERA->SetScale(Vector2(0.75f, 0.75f));
	_stool1->SetTarget(_player);
	_stool2->SetTarget(_player);

	_player->SetPosition(Vector2(200, 520));
}

MapTool::~MapTool()
{
}

void MapTool::Update()
{
	_player->Update();

	_stool1->Update();
	_stool2->Update();
}

void MapTool::Render()
{
	_player->Render();

	_stool1->Render();
	_stool2->Render();
}

void MapTool::PostRender()
{
}

void MapTool::PreRender()
{
}
