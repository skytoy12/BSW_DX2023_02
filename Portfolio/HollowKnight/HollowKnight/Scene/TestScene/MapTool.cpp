#include "framework.h"
#include "MapTool.h"

MapTool::MapTool()
{
	_player = make_shared<Player>();
	_rMon = make_shared<RushMonster>();
	_Potal = make_shared<CircleCollider>(50);

	_Vbricks = make_shared<VectorBrick>(230);

	_Vbricks->SetName("GameScene5");
	_Vbricks->SetSaveFile(L"Info/BrickInfoGameScene5.BSW");
	_Vbricks->SetImageSaveName(L"GameScene5.image");




	for (int i = 0; i < 8; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>(Vector2(50, 50));
		_walls.push_back(wall);
	}



	for (auto wall : _walls)
	{
		wall->SetTarget(_player);
	}

	CAMERA->SetTarget(nullptr);
	//CAMERA->SetTarget(_player->GetTransform());

	CreateMap();

	_rMon->SetPlayer(_player);
	_player->SetPosition(Vector2(-3400, +150));
	_rMon->SetPosition(Vector2(-300, -900));
	_Potal->SetPosition(Vector2(-2761, -774));
}

MapTool::~MapTool()
{
}

void MapTool::Update()
{
	_player->Update();
	_rMon->Update();
	_Potal->Update();
	_Vbricks->Update();

	CAMERA->SetScale(Vector2(_scale, _scale));
	//MoveCol();



	if (_isOn == true && _Potal->IsCollision(_player->GetCollider()))
	{
		_isOn = false;
		CAMERA->SetTarget(nullptr);
		SCENE->NextScene();
	}


	for (auto wall : _walls)
	{
		wall->Update();
	}



	for (auto wall : _walls)
	{
		wall->BlockR(RECT(_rMon->GetCollider()));
	}

	DashCut();

	if (KEY_UP(VK_UP))
		_colNum += 1;

	if (KEY_UP(VK_DOWN))
		_colNum -= 1;
}

void MapTool::Render()
{

	_player->Render();
	_rMon->Render();
	_Potal->Render();



	_Vbricks->Render();

	for (auto wall : _walls)
	{
		wall->Render();
	}



}

void MapTool::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	_Vbricks->PostRender();

}

void MapTool::PreRender()
{

}

void MapTool::CreateMap()
{
	_walls[0]->SetPosition(Vector2(+0, -250));
	_walls[1]->SetPosition(Vector2(-2000, +600));
	_walls[2]->SetPosition(Vector2(+1500, +600));
	_walls[3]->SetPosition(Vector2(-1035, -250));
	_walls[4]->SetPosition(Vector2(+1035, -250));


	_walls[0]->SetScale(Vector2(150, 6));
	_walls[1]->SetScale(Vector2(30, 10));
	_walls[2]->SetScale(Vector2(15, 50));
	_walls[3]->SetScale(Vector2(30, 6));
	_walls[4]->SetScale(Vector2(30, 6));
}

void MapTool::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_walls[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}

}

void MapTool::DashCut()
{
	for (auto wall : _walls)
	{
		_player->CutDashW(wall);
	}

	if (KEY_DOWN(VK_SHIFT))
	{
		_player->Dash();
	}
}

