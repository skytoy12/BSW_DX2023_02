#include "framework.h"
#include "Player.h"

using namespace tinyxml2;

#pragma region Player

Player::Player()
{
	_col = make_shared<CircleCollider>(50);


	CreateAction(L"Resource/Player/Run.png", "Resource/Player/Run.xml", "Run", Vector2(75, 120), Action::Type::LOOP);
	


	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 9.876));


}

Player::~Player()
{
}

void Player::Update()
{
	_col->Update();
	_actions[0]->Update();
	_sprites[0]->Update();
	_transform->Update();

	Input();
	Select();
}

void Player::Render()
{
	_transform->SetBuffer(0);
	_sprites[0]->SetCurClip(_actions[0]->GetCurClip());
	_sprites[0]->Render();
	_col->Render();
}

void Player::PostRender()
{
}

#pragma endregion

#pragma region Update Funtion


void Player::Input()
{
	if (KEY_PRESS('A'))
	{
		_sprites[_curstate]->SetRight();
	}

	if (KEY_PRESS('D'))
	{
		_sprites[_curstate]->SetLeft();
	}
}

void Player::Select()
{
	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-500.0f, 0.0f);
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(500.0f, 0.0f);
		Move(movePos);
	}
}

#pragma endregion

#pragma region NoUpdate

void Player::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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
	_actions.push_back(action);
	_sprites.push_back(sprite);
}


void Player::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}

#pragma endregion
