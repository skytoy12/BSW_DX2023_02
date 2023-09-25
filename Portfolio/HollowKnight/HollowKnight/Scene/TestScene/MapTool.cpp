#include "framework.h"
#include "MapTool.h"

MapTool::MapTool()
{
	_player = make_shared<Player>();
	_rMon = make_shared<RushMonster>();
	_Potal = make_shared<CircleCollider>(50);

	_Vbricks = make_shared<VectorBrick>();

	_Vbricks->SetName("GameScene2");
	_Vbricks->SetSaveFile(L"Info/BrickInfoGameScene2.BSW");
	_Vbricks->SetImageSaveName(L"GameScene2.image");

	for (int i = 0; i < 15; i++)
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
	_player->SetPosition(Vector2(0, 1000));
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
		//SCENE->NextScene();
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
	_walls[0]->SetPosition(Vector2(-250, +230));
	_walls[1]->SetPosition(Vector2(+250, +230));
	_walls[2]->SetPosition(Vector2(+0, -700));
	_walls[3]->SetPosition(Vector2(-1400, -750));
	_walls[4]->SetPosition(Vector2(-887, -1047));
	_walls[5]->SetPosition(Vector2(-330, -1125));
	_walls[6]->SetPosition(Vector2(-50, -900));
	_walls[7]->SetPosition(Vector2(-250, +770));
	_walls[8]->SetPosition(Vector2(+250, +770));
	_walls[9]->SetPosition(Vector2(+280, -344));
	_walls[10]->SetPosition(Vector2(-1887, -1047));
	_walls[11]->SetPosition(Vector2(-2320, -1100));
	_walls[12]->SetPosition(Vector2(-2358, -635));
	_walls[13]->SetPosition(Vector2(-2760, -1060));
	_walls[14]->SetPosition(Vector2(-2760, -450));

	_walls[0]->SetScale(Vector2(2, 10));
	_walls[1]->SetScale(Vector2(2, 10));
	_walls[2]->SetScale(Vector2(20, 3));
	_walls[3]->SetScale(Vector2(20, 4));
	_walls[4]->SetScale(Vector2(3, 8));
	_walls[5]->SetScale(Vector2(20, 4));
	_walls[6]->SetScale(Vector2(3, 5));
	_walls[7]->SetScale(Vector2(2, 10));
	_walls[8]->SetScale(Vector2(2, 10));
	_walls[9]->SetScale(Vector2(2, 12));
	_walls[10]->SetScale(Vector2(3, 8));
	_walls[11]->SetScale(Vector2(15, 3));
	_walls[12]->SetScale(Vector2(8, 3));
	_walls[13]->SetScale(Vector2(3, 8));
	_walls[14]->SetScale(Vector2(3, 8));
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

