#include "framework.h"
#include "Cup_Boss.h"
using namespace tinyxml2;

Cup_Boss::Cup_Boss()
{
	_collider = make_shared<CircleCollider>(150);


	CreateAction(L"Resource/CupHead/Clown_Page_Last_Spawn_Penguin_Start.png", "Resource/CupHead/Clown_Page_Last_Spawn_Penguin_Start.xml", "START", Vector2(400, 400));
	_actions[0]->SetType(Action::Type::END);
	CreateAction(L"Resource/CupHead/Clown_Page_Last_Spawn_Penguin_Loop.png", "Resource/CupHead/Clown_Page_Last_Spawn_Penguin_Loop.xml", "LOOP", Vector2(400, 400));
	_actions[1]->SetType(Action::Type::END);
	CreateAction(L"Resource/CupHead/Clown_Page_Last_Spawn_Penguin_End.png", "Resource/CupHead/Clown_Page_Last_Spawn_Penguin_End.xml", "END", Vector2(400, 400));
	_actions[2]->SetType(Action::Type::END);

	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
	_actions[0]->SetEndEvent(std::bind(&Cup_Boss::EndEvent, this));
	_actions[1]->SetEndEvent(std::bind(&Cup_Boss::EndEvent, this));
	_actions[2]->SetEndEvent(std::bind(&Cup_Boss::EndEvent, this));
}

Cup_Boss::~Cup_Boss()
{
}

void Cup_Boss::Update()
{
	if (_state == Boss_State::START && _isEnd == true)
	{
		_isEnd = false;
		_state = Boss_State::LOOP;
		_actions[_state]->Stop();
		_actions[_state]->Play();
	}

	if (_state == Boss_State::LOOP && _isEnd == true)
	{
		_isEnd = false;
		_state = Boss_State::END;
		_actions[_state]->Stop();
		_actions[_state]->Play();
	}

	if (_state == Boss_State::END && _isEnd == true)
	{
		_isEnd = false;
		_state = Boss_State::START;
		_actions[_state]->Stop();
		_actions[_state]->Play();
	}

	_collider->Update();

	_actions[_state]->Update();

	_sprites[_state]->Update();

	_transform->Update();
}

void Cup_Boss::Render()
{
	_transform->SetBuffer(0);

	_sprites[_state]->SetCurFrame(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();

	_collider->Render();
}

void Cup_Boss::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size)
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

	shared_ptr<Action> action = make_shared<Action>(clips, actionName);
	action->Play();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Boss::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Boss::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
