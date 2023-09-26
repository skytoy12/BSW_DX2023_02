#include "framework.h"
#include "GameScene3.h"

GameScene3::GameScene3()
{
	_player = make_shared<Player>();


	_stoolA = make_shared<Stool>(L"Resource/Stool/stool2.png", Vector2(131, 106), Vector2(110, 50));
	_stoolB = make_shared<Stool>(L"Resource/Stool/stool3.png", Vector2(101,  68), Vector2(90, 48));
	_stoolC = make_shared<Stool>(L"Resource/Stool/stool4.png", Vector2(125, 103), Vector2(110, 50));
	_stoolD = make_shared<Stool>(L"Resource/Stool/stool5.png", Vector2(641, 286), Vector2(520, 100));

	_backGround = make_shared<BackGround>(L"Resource/UI/BackGround.webp", Vector2(800 * 4, 505 * 4));
	_backGround1 = make_shared<BackGround>(L"Resource/UI/BackGround.webp", Vector2(800 * 4, 505 * 4));
	_backGround2 = make_shared<BackGround>(L"Resource/UI/BackGround.webp", Vector2(800 * 4, 505 * 4));
	_backGround3 = make_shared<BackGround>(L"Resource/UI/BackGround.webp", Vector2(800 * 4, 505 * 4));

	_fly = make_shared<FlyMonster>(Vector2(1471, 376));

	_Potal = make_shared<CircleCollider>(50);

	for (int i = 0; i < 215; i++)
	{
		shared_ptr<BrickImage> image = make_shared<BrickImage>(L"Resource/Deco/44.png", Vector2(275.0f, 273.0f));
		image->_isActive = false;
		_images.push_back(image);
	}

	for (int i = 0; i < 8; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>(Vector2(50, 50));
		_walls.push_back(wall);
	}

	for (int i = 0; i < 3; i++)
	{
		shared_ptr<Stool> stool = make_shared<Stool>(L"Resource/Stool/stool1.png", Vector2(169, 199), Vector2(135, 120));
		_stools.push_back(stool);
	}

	for (int i = 0; i < 1; i++)
	{
		shared_ptr<RushMonster> rmon = make_shared<RushMonster>();
		_RMons.push_back(rmon);
	}

	for (int i = 0; i < 2; i++)
	{
		shared_ptr<JumpMonster> jmon = make_shared<JumpMonster>();
		_JMons.push_back(jmon);
	}

	for (auto wall : _walls)
	{
		wall->SetTarget(_player);
	}

	for (auto stool : _stools)
	{
		stool->SetTarget(_player);
	}

	_stoolA->SetTarget(_player);
	_stoolB->SetTarget(_player);
	_stoolC->SetTarget(_player);
	_stoolD->SetTarget(_player);

	for (auto rmon : _RMons)
	{
		rmon->SetPlayer(_player);
	}

	for (auto jmon : _JMons)
	{
		jmon->SetPlayer(_player);
	}

	_fly->SetPlayer(_player);

	for (auto stool : _stools)
	{
		stool->GetTransform()->SetPosition(Vector2(0, -20));
	}

	_stoolA->GetTransform()->SetPosition(Vector2(0, -15));
	_stoolC->GetTransform()->SetPosition(Vector2(0, -15));
	_stoolD->GetTransform()->SetPosition(Vector2(20, -35));

	_stoolA->SetScale(Vector2(1.3f, 1.3f));
	_stoolB->SetScale(Vector2(1.3f, 1.3f));
	_stoolC->SetScale(Vector2(1.3f, 1.3f));

	//CAMERA->SetTarget(nullptr);
	//CAMERA->SetTarget(_player->GetTransform());

	_player->SetPosition(Vector2(-1887, - 253));
	_Potal->SetPosition(Vector2(+2753, + 234));
	_backGround->SetPosition(Vector2(-1887, -253));
	_backGround1->SetPosition(Vector2(0, -253));
	_backGround2->SetPosition(Vector2(1900, 150));
	_backGround3->SetPosition(Vector2(1900, 1200));

	CreateMap();
	BrickLoad();
}

GameScene3::~GameScene3()
{
}

void GameScene3::Update()
{

	if (_start == true)
	{
		_start = false;
		Load();
		CAMERA->SetTarget(_player->GetTransform());
	}

	CAMERA->SetLeftBottom(Vector2(-1600, -580));
	CAMERA->SetRightTop(Vector2(+1900, +1100));

	_player->Update();
	_fly->Update();
	_stoolA->Update();
	_stoolB->Update();
	_stoolC->Update();
	_stoolD->Update();
	_Potal->Update();
	for (auto image : _images)
		image->Update();

	_backGround->Update();
	_backGround1->Update();
	_backGround2->Update();
	_backGround3->Update();

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

	for (auto rmon : _RMons)
	{
		rmon->Update();
	}

	for (auto jmon : _JMons)
	{
		jmon->Update();
	}

	for (auto wall : _walls)
	{
		for (auto rmon : _RMons)
		{
			wall->BlockR(RECT(rmon->GetCollider()));
		}

		for (auto jmon : _JMons)
		{
			wall->BlockR(RECT(jmon->GetCollider()));
		}	
	}

	for (auto stool : _stools)
	{
		for (auto rmon : _RMons)
		{
			stool->BlockR(RECT(rmon->GetCollider()));
		}

		for (auto jmon : _JMons)
		{
			stool->BlockR(RECT(jmon->GetCollider()));
		}
	}

	DashCut();

	if (KEY_UP(VK_UP))
		_colNum += 1;

	if (KEY_UP(VK_DOWN))
		_colNum -= 1;
}

void GameScene3::Render()
{

	_backGround->Render();
	_backGround3->Render();
	_backGround1->Render();
	_backGround2->Render();

	_player->Render();
	_stoolA->Render();
	_stoolB->Render();
	_stoolC->Render();
	_stoolD->Render();
	_Potal->Render();

	for (auto wall : _walls)
	{
		wall->Render();
	}

	for (auto stool : _stools)
	{
		stool->Render();
	}

	for (auto rmon : _RMons)
	{
		rmon->Render();
	}

	for (auto jmon : _JMons)
	{
		jmon->Render();
	}

	for (auto image : _images)
		image->Render();

	_fly->Render();
}

void GameScene3::PostRender()
{
	_player->PostRender();
	//_rMon->PostRender();

	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	ImGui::Text("colNum : %d", _colNum);
}

void GameScene3::PreRender()
{
}

void GameScene3::CreateMap()
{
	_walls[0]->SetPosition(Vector2(- 135, - 797));
	_walls[1]->SetPosition(Vector2(- 947, - 493));
	_walls[2]->SetPosition(Vector2(+ 349, - 243));
	_walls[3]->SetPosition(Vector2(+ 349, + 831));
	_walls[4]->SetPosition(Vector2(+ 528, - 264));
	_walls[5]->SetPosition(Vector2(+ 808, - 443));
	_walls[6]->SetPosition(Vector2(+ 885, + 740));
	_walls[7]->SetPosition(Vector2(+2565, - 671));

	_walls[0]->SetScale(Vector2(100, 10));
	_walls[1]->SetScale(Vector2(  5,  5));
	_walls[2]->SetScale(Vector2(  5, 15));
	_walls[3]->SetScale(Vector2(  5, 15));
	_walls[4]->SetScale(Vector2(  4,  8));
	_walls[5]->SetScale(Vector2(  8,  4));
	_walls[6]->SetScale(Vector2(  3, 34));
	_walls[7]->SetScale(Vector2( 10, 34));

	_stools[0]->SetPosition(Vector2(- 489, - 227));
	_stools[1]->SetPosition(Vector2(-  85, -  84));
	_stools[2]->SetPosition(Vector2(+1743, - 227));

	_stoolA->SetPosition(Vector2(+1351, - 237));
	_stoolB->SetPosition(Vector2(+2000, + 313));
	_stoolC->SetPosition(Vector2(+2080, -  60));
	_stoolC->SetPosition(Vector2(+2080, -  60));
	_stoolD->SetPosition(Vector2(+1544, + 103));

	_JMons[0]->SetPosition(Vector2(+  59, -300));
	_JMons[1]->SetPosition(Vector2(+1999, -300));

	_RMons[0]->SetPosition(Vector2(- 636, -300));
}

void GameScene3::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			//_walls[_colNum]->SetPosition(W_MOUSE_POS);
			_stoolD->SetPosition(W_MOUSE_POS);
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

void GameScene3::DashCut()
{
	for (auto wall : _walls)
	{
		_player->CutDashW(wall);
	}

	for (auto stool : _stools)
	{
		_player->CutDashS(stool);
	}

	_player->CutDashS(_stoolA);
	_player->CutDashS(_stoolB);
	_player->CutDashS(_stoolC);
	_player->CutDashS(_stoolD);

	if (KEY_DOWN(VK_SHIFT))
	{
		_player->Dash();
	}
}

void GameScene3::Save()
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

void GameScene3::Load()
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

void GameScene3::BrickLoad()
{
	vector<BrickInfo> brickInfo;

	BinaryReader reader = BinaryReader(L"Info/BrickInfoGameScene3.BSW");
	string infoName = reader.String();

	if (infoName == "GameScene3")
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

	BinaryReader data(L"Info/GameScene3.image");

	for (shared_ptr<BrickImage> image : _images)
	{
		image->SetSRV(data.WString());
	}
}
