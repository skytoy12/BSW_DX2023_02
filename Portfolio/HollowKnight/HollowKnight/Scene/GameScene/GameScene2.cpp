#include "framework.h"
#include "GameScene2.h"

GameScene2::GameScene2()
{
	_player = make_shared<Player>();
	_Potal = make_shared<CircleCollider>(50);
	_RMon = make_shared<RushMonster>();
	_JMon = make_shared<JumpMonster>();

	for (int i = 0; i < 5; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>(Vector2(50, 50));
		_walls.push_back(wall);
	}

	for (int i = 0; i < 9; i++)
	{
		shared_ptr<Stool> stool = make_shared<Stool>(L"Resource/Stool/stool5.png", Vector2(641, 286), Vector2(520, 100));
		_stools.push_back(stool);
	}

	for (int i = 0; i < 4; i++)
	{
		shared_ptr<FlyMonster> fly = make_shared<FlyMonster>(Vector2(0, 0));
		_flies.push_back(fly);
	}

	for (auto wall : _walls)
	{
		wall->SetTarget(_player);
	}

	for (auto stool : _stools)
	{
		stool->SetTarget(_player);
	}

	for (auto fly : _flies)
	{
		fly->SetPlayer(_player);
	}

	for (auto stool : _stools)
	{
		stool->GetTransform()->SetPosition(Vector2(20, -35));
	}

	_JMon->SetPlayer(_player);
	_RMon->SetPlayer(_player);

	//CAMERA->SetTarget(nullptr);
	//CAMERA->SetTarget(_player->GetTransform());

	_player->SetPosition(Vector2(888, 1215));
	_JMon->SetPosition(Vector2(-1343, - 984));
	_RMon->SetPosition(Vector2(+ 356, -1005));
	_Potal->SetPosition(Vector2(+ 914, -1284));

	CreateMap();
}

GameScene2::~GameScene2()
{
}

void GameScene2::Update()
{

	if (_start == true)
	{
		_start = false;
		Load();
		CAMERA->SetTarget(_player->GetTransform());
	}
	_player->Update();
	_RMon->Update();
	_JMon->Update();
	_Potal->Update();

	if (_isOn == true && _Potal->IsCollision(_player->GetCollider()))
	{
		_isOn = false;
		Save();
		CAMERA->SetTarget(nullptr);
		SCENE->NextScene();
	}

	CAMERA->SetScale(Vector2(_scale, _scale));
	MoveCol();

	for (auto wall : _walls)
	{
		wall->Update();
	}

	for (auto stool : _stools)
	{
		stool->Update();
	}

	for (auto fly : _flies)
	{
		fly->Update();
	}

	for (auto wall : _walls)
	{
		wall->BlockR(RECT(_RMon->GetCollider()));
		wall->BlockR(RECT(_JMon->GetCollider()));
	}

	DashCut();

	if (KEY_UP(VK_UP))
		_colNum += 1;

	if (KEY_UP(VK_DOWN))
		_colNum -= 1;
}

void GameScene2::Render()
{
	_player->Render();
	_RMon->Render();
	_JMon->Render();
	_Potal->Render();
	for (auto wall : _walls)
	{
		wall->Render();
	}

	for (auto stool : _stools)
	{
		stool->Render();
	}

	for (auto fly : _flies)
	{
		fly->Render();
	}
}

void GameScene2::PostRender()
{
	_player->PostRender();
	//_rMon->PostRender();

	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	ImGui::Text("colNum : %d", _colNum);
	ImGui::Text("origin : %.1f, %.1f", _flies[0]->GetOrigin().x, _flies[0]->GetOrigin().y);
}

void GameScene2::PreRender()
{
}

void GameScene2::CreateMap()
{
	_walls[0] ->SetPosition(Vector2(+ 585, + 919));
	_walls[1] ->SetPosition(Vector2(- 540, + 515));
	_walls[2] ->SetPosition(Vector2(- 300, -1451));
	_walls[3] ->SetPosition(Vector2(-2551, + 207));
	_walls[4] ->SetPosition(Vector2(+1212, + 207));


	_walls[0] ->SetScale(Vector2(15,  3));
	_walls[1] ->SetScale(Vector2(15,  5));
	_walls[2] ->SetScale(Vector2(80,  5));
	_walls[3] ->SetScale(Vector2(10, 100));
	_walls[4] ->SetScale(Vector2(10, 100));

	_stools[0]->SetPosition(Vector2(+   0, +   0));
	_stools[1]->SetPosition(Vector2(- 977, - 195));
	_stools[2]->SetPosition(Vector2(- 355, - 395));
	_stools[3]->SetPosition(Vector2(+ 192, - 595));
	_stools[4]->SetPosition(Vector2(-1417, + 496));
	_stools[5]->SetPosition(Vector2(-1835, + 233));
	_stools[6]->SetPosition(Vector2(-1411, +  48));
	_stools[7]->SetPosition(Vector2(- 896, - 629));
	_stools[8]->SetPosition(Vector2(- 372, - 929));


	_stools[3]->SetScale(Vector2(0.6f, 1.0f));
	_stools[5]->SetScale(Vector2(0.4f, 1.0f));
	_stools[6]->SetScale(Vector2(0.7f, 1.0f));
	_stools[7]->SetScale(Vector2(1.2f, 1.0f));
	_stools[8]->SetScale(Vector2(2.0f, 1.0f));

	_flies[0]->SetPosition(Vector2(- 829, + 931));
	_flies[1]->SetPosition(Vector2(-1509, + 247));
	_flies[2]->SetPosition(Vector2(- 416, -  89));
	_flies[3]->SetPosition(Vector2(- 316, - 715));
}

void GameScene2::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_walls[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}

	if (KEY_PRESS('Z'))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_stools[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}
}

void GameScene2::DashCut()
{
	for (auto wall : _walls)
	{
		_player->CutDashW(wall);
	}

	for (auto stool : _stools)
	{
		_player->CutDashS(stool);
	}

	if (KEY_DOWN(VK_SHIFT))
	{
		_player->Dash();
	}
}

void GameScene2::Save()
{
	PlayerInfo playerInfo;


	int Php = _player->GetHP();
	int Pmp = _player->GetMP();

	playerInfo.hp = Php;
	playerInfo.mp = Pmp;

	BinaryWriter writer = BinaryWriter(L"Info/HpMp.save");
	writer.String("PlayerInfo");
	writer.UInt(sizeof(playerInfo));
	writer.Byte(&playerInfo, sizeof(playerInfo));
}

void GameScene2::Load()
{
	PlayerInfo playerInfo;

	BinaryReader reader = BinaryReader(L"Info/HpMp.save");
	string infoName = reader.String();

	if (infoName == "PlayerInfo")
	{
		UINT size = reader.UInt();

		void* ptr = &playerInfo;
		reader.Byte(&ptr, size);
	}

	_player->SetHP(playerInfo.hp);
	_player->SetMP(playerInfo.mp);
}
