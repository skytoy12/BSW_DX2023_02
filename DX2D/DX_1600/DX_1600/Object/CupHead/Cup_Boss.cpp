#include "framework.h"
#include "Cup_Boss.h"
using namespace tinyxml2;

Cup_Boss::Cup_Boss()
{
	_collider = make_shared<RectCollider>(Vector2(Vector2(200, 150)));
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

	_transform->SetPosition(Vector2(20, 30));
	_intBuffer = make_shared<IntBuffer>();
	_intBuffer->_data.aInt = 3;
	_intBuffer->_data.bInt = 300;
	
	CreateAction(L"Resource/CupHead/Boss/Clown_Intro_1.png", "Resource/CupHead/Boss/Clown_Intro_1.xml", "START", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Intro_2.png", "Resource/CupHead/Boss/Clown_Intro_2.xml", "LOOP", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEventDash, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Move_1.png", "Resource/CupHead/Boss/Clown_Move_1.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Move_2.png", "Resource/CupHead/Boss/Clown_Move_2.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Move_3.png", "Resource/CupHead/Boss/Clown_Move_3.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Ready_Dash.png", "Resource/CupHead/Boss/Clown_Ready_Dash.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Dash.png", "Resource/CupHead/Boss/Clown_Dash.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Dash_Loop.png", "Resource/CupHead/Boss/Clown_Dash_Loop.xml", "END", Vector2(600, 400), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/Boss/Clown_Wall_Crash.png", "Resource/CupHead/Boss/Clown_Wall_Crash.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEventCrash, this));
	CreateAction(L"Resource/CupHead/Boss/Clown_Die_Middle.png", "Resource/CupHead/Boss/Clown_Die_Middle.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::DieEvent, this));


	SetRight();

	//action Event ¼³Á¤
	{
		_actions[Boss_State::START]->SetAlmostEvent(std::bind(&Cup_Boss::EndEvent, this));
	}




}

Cup_Boss::~Cup_Boss()
{
}

void Cup_Boss::Update()
{
	if (_isAlive == false)
		return;

	_collider->Update();
	_intBuffer->Update();
	_actions[_state]->Update();

	_sprites[_state]->Update();

	_transform->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());

	Dash();

	if (_isWallCrash == true)
	{
		_state = Boss_State::DASHSTOP;
		_actions[_state]->Play();
		_actions[DASHLOOP]->Reset();
		_isWallCrash = false;
	}

	if (_hp <= 0)
	{
		_state = DIE;
		_sprites[_state]->SetPS(ADD_PS(L"Shader/ActionFilterPS.hlsl"));

		if (_intBuffer->_data.bInt <= 1)
			_intBuffer->_data.bInt = 100;
		_intBuffer->_data.bInt -= 1;
	}
}

void Cup_Boss::Render()
{
	if (_isAlive == false)
		return;
	_transform->SetBuffer(0);
	_intBuffer->SetPSBuffer(1);


	_sprites[_state]->Render();

	_collider->Render();
}

void Cup_Boss::PostRender()
{
	ImGui::Text("BossHP : %d", _hp);
	 ImGui::SliderInt("State", (int*)&_state, 0, 9);
	//ImGui::SliderInt("Mosaic", &_intBuffer->_data.bInt, 0, 300);
}

void Cup_Boss::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmmlPath.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;


	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Boss::Dash()
{
	if (_state == Boss_State::DASHSTART || _state == Boss_State::DASHLOOP)
	{
		if (_isLeft == true)
		{
			Vector2 movePos = Vector2(-500.0f, 0.0f);
			Move(movePos);
		}
		else
		{
			Vector2 movePos = Vector2(500.0f, 0.0f);
			Move(movePos);
		}
	}
}

void Cup_Boss::EndEventDash()
{
	if (_coolDown > 0) 
	{
		_state = Boss_State::LOOP;
		_actions[_state]->Play();
		_coolDown -= 1;
		return;
	}
	if (_coolDown <= 0)
	{
		_state = Boss_State::READY1;
		_actions[_state]->Play();
		_coolDown -= RandomNum(1, 4);
		return;
	}
}

void Cup_Boss::EndEvent()
{
	if (_state == Boss_State::START)
	{
		_state = Boss_State::LOOP;
		_actions[_state]->Play();
		_actions[START]->Reset();
		return;
	}

	if (_state == Boss_State::READY1)
	{
		_state = Boss_State::READY2;
		_actions[_state]->Play();
		_actions[READY1]->Reset();
		return;
	}

	if (_state == Boss_State::READY2)
	{
		_state = Boss_State::READY3;
		_actions[_state]->Play();
		_actions[READY2]->Reset();
		return;
	}


	if (_state == Boss_State::READY3)
	{
		_state = Boss_State::DASHREADY;
		_actions[_state]->Play();
		_actions[READY3]->Reset();
		return;
	}

	if (_state == Boss_State::DASHREADY)
	{
		_state = Boss_State::DASHSTART;
		_actions[_state]->Play();
		_actions[DASHREADY]->Reset();
		return;
	}

	if (_state == Boss_State::DASHSTART)
	{
		_state = Boss_State::DASHLOOP;
		_actions[_state]->Play();
		_actions[DASHSTART]->Reset();
		return;
	}
}

void Cup_Boss::DieEvent()
{
	_isAlive = false;
}

void Cup_Boss::EndEventCrash()
{
	_state = Boss_State::LOOP;
	_actions[_state]->Play();
	_actions[DASHSTOP]->Reset();
	if (_isLeft == true)
	{
		SetLeft();
	}
	else
	{
		SetRight();
	}
	return;
}

void Cup_Boss::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
	_isLeft = false;
}

void Cup_Boss::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
	_isLeft = true;
}
