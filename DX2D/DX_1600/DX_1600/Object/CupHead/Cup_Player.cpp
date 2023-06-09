#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	_collider = make_shared<CircleCollider>(50);

	CreateIdleAction();
	CreateRunAction();

	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
	_transform->SetPosition(Vector2(0, 9.876));

}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Select();

	_collider->Update();

	_actions[_state]->Update();

	if (_state == Cup_Player::State::IDLE)
		_idleSprite->Update();

	if (_state == Cup_Player::State::RUN)
		_runSprite->Update();

	_transform->Update();
}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);

	if (_state == Cup_Player::State::IDLE)
	{
		_idleSprite->SetCurFrame(_actions[_state]->GetCurClip());
		_idleSprite->Render();
	}

	if (_state == Cup_Player::State::RUN)
	{
		_runSprite->SetCurFrame(_actions[_state]->GetCurClip());
		_runSprite->Render();
	}

	_collider->Render();
}

void Cup_Player::PostRender()
{
	//ImGui::SliderFloat2("FixedPos", (float*)&_fixedPos, 0, 100);
	//_transform->SetPosition(_fixedPos);
}

void Cup_Player::Select()
{

	if (KEY_PRESS('A'))
	{
		_state = Cup_Player::State::RUN;
		Vector2 movePos = Vector2(-500.0f, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		_state = Cup_Player::State::RUN;
		Vector2 movePos = Vector2(500.0f, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_UP('D'))
	{
		_state = Cup_Player::State::IDLE;
	}

	if (KEY_UP('A'))
	{
		_state = Cup_Player::State::IDLE;

	}
}

void Cup_Player::CreateIdleAction()
{
	wstring srvPath = L"Resource/CupHead/Idle.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Idle.xml";
	document->LoadFile(path.c_str());

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

	shared_ptr<Action> action = make_shared<Action>(clips, "Cup_IDLE");
	action->Play();
	_actions.push_back(action);
	_idleSprite = make_shared<Sprite>(srvPath, Vector2(250, 250));
}

void Cup_Player::CreateRunAction()
{
	wstring srvPath = L"Resource/CupHead/Run.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Run.xml";
	document->LoadFile(path.c_str());

	XMLElement* texturAtlas = document->FirstChildElement();
	XMLElement* row = texturAtlas->FirstChildElement();

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

	shared_ptr<Action> action = make_shared<Action>(clips, "CUP_RUN");
	action->Play();
	_runSprite = make_shared<Sprite>(srvPath, Vector2(120, 120));
	_actions.push_back(action);
}
