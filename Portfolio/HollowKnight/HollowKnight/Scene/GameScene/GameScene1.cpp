#include "framework.h"
#include "GameScene1.h"

GameScene1::GameScene1()
{
	_player = make_shared<Player>();
	_rMon = make_shared<RushMonster>();
	_Potal = make_shared<CircleCollider>(50);
	_backGround = make_shared<BackGround>(L"Resource/UI/BackGround.webp", Vector2(800 * 4, 505 * 4));
	_backGround1 = make_shared<BackGround>(L"Resource/UI/BackGround.webp", Vector2(800 * 4, 505 * 4));
	for (int i = 0; i < 230; i++)
	{
		shared_ptr<BrickImage> image = make_shared<BrickImage>(L"Resource/Deco/44.png", Vector2(275.0f, 273.0f));
		image->_isActive = false;
		_images.push_back(image);
	}

	for (int i = 0; i < 15; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>(Vector2(50, 50));
		_walls.push_back(wall);
	}

	for (auto wall : _walls)
	{
		wall->SetTarget(_player);
	}

	//CAMERA->SetTarget(nullptr);
	CAMERA->SetTarget(_player->GetTransform());

	CreateMap();
	BrickLoad();

	_rMon->SetPlayer(_player);
	_player->SetPosition(Vector2(0, 1000));
	_rMon->SetPosition(Vector2(-300, -900));
	_Potal->SetPosition(Vector2(-2761, -774));
	_backGround->SetPosition(Vector2(0, -500));
	_backGround1->SetPosition(Vector2(-3000, -500));
}

GameScene1::~GameScene1()
{

}

void GameScene1::Update()
{
	CAMERA->SetLeftBottom(Vector2(-2100, - 900));
	CAMERA->SetRightTop  (Vector2(+ 400, + 120));
	_player->Update();
	_rMon->Update();
	_Potal->Update();
	_backGround->Update();
	_backGround1->Update();
	for (auto image : _images)
		image->Update();

	CAMERA->SetScale(Vector2(_scale, _scale));
	MoveCol();


	if (_isOn == true && _Potal->IsCollision(_player->GetCollider()))
	{
		_isOn = false;
		Save();
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

void GameScene1::Render()
{
	_backGround->Render();
	_backGround1->Render();
	_player->Render();
	_rMon->Render();
	_Potal->Render();

	for (auto image : _images)
		image->Render();

	for (auto wall : _walls)
	{
		wall->Render();
	}

}

void GameScene1::PostRender()
{
	_player->PostRender();
	_rMon->PostRender();

	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	ImGui::Text("colNum : %d", _colNum);
}

void GameScene1::PreRender()
{

}

void GameScene1::CreateMap()
{
	_walls[0] ->SetPosition(Vector2(- 250, + 230));
	_walls[1] ->SetPosition(Vector2(+ 250, + 230));
	_walls[2] ->SetPosition(Vector2(+   0, - 700));
	_walls[3] ->SetPosition(Vector2(-1400, - 750));
	_walls[4] ->SetPosition(Vector2(- 887, -1047));
	_walls[5] ->SetPosition(Vector2(- 330, -1125));
	_walls[6] ->SetPosition(Vector2(-  50, - 900));
	_walls[7] ->SetPosition(Vector2(- 250, + 770));
	_walls[8] ->SetPosition(Vector2(+ 250, + 770));
	_walls[9] ->SetPosition(Vector2(+ 280, - 344));
	_walls[10]->SetPosition(Vector2(-1887, -1047));
	_walls[11]->SetPosition(Vector2(-2320, -1100));
	_walls[12]->SetPosition(Vector2(-2358, - 635));
	_walls[13]->SetPosition(Vector2(-2760, -1060));
	_walls[14]->SetPosition(Vector2(-2760, - 450));

	_walls[0] ->SetScale(Vector2( 2, 10));
	_walls[1] ->SetScale(Vector2( 2, 10));
	_walls[2] ->SetScale(Vector2(20,  3));
	_walls[3] ->SetScale(Vector2(20,  4));
	_walls[4] ->SetScale(Vector2( 3,  8));
	_walls[5] ->SetScale(Vector2(20,  4));
	_walls[6] ->SetScale(Vector2( 3,  5));
	_walls[7] ->SetScale(Vector2( 2, 10));
	_walls[8] ->SetScale(Vector2( 2, 10));
	_walls[9] ->SetScale(Vector2( 2, 12));
	_walls[10]->SetScale(Vector2( 3,  8));
	_walls[11]->SetScale(Vector2(15,  3));
	_walls[12]->SetScale(Vector2( 8,  3));
	_walls[13]->SetScale(Vector2( 3,  8));
	_walls[14]->SetScale(Vector2( 3,  8));
}

void GameScene1::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_walls[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}

}

void GameScene1::DashCut()
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

void GameScene1::Save()
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

void GameScene1::Load()
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

void GameScene1::BrickLoad()
{
	vector<BrickInfo> brickInfo;

	BinaryReader reader = BinaryReader(L"Info/BrickInfoGameScene1.BSW");
	string infoName = reader.String();

	if (infoName == "GameScene1")
	{
		UINT size = reader.UInt();
		brickInfo.resize(size);

		void* ptr = brickInfo.data();
		reader.Byte(&ptr, size * sizeof(BrickInfo));
	}

	for (int i = 0; i < brickInfo.size(); i++)
	{
		if (i >= _images.size() - 1)
			break;

		_images[i]->SetPosition(brickInfo[i].pos);
		_images[i]->SetScale(brickInfo[i].Scale);
		_images[i]->_isActive = true;
	}

	BinaryReader data(L"Info/GameScene1.image");

	for (shared_ptr<BrickImage> image : _images)
	{
		image->SetSRV(data.WString());
	}
}


