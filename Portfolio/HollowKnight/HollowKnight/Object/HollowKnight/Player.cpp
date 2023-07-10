#include "framework.h"
#include "Player.h"

using namespace tinyxml2;

#pragma region Player

Player::Player()
{
	_col = make_shared<RectCollider>(Vector2(50, 100));
	_weaponCol = make_shared<RectCollider>(Vector2(50, 10));
	CreateAction(L"Resource/Player/Idle.png", "Resource/Player/Idle.xml", "Idle", Vector2(61, 130), Action::Type::LOOP);
	CreateAction(L"Resource/Player/Run.png", "Resource/Player/Run.xml", "Run", Vector2(75, 120), Action::Type::LOOP);

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_weaponCol->GetTransform()->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 9.876));


}

Player::~Player()
{
}

void Player::Update()
{
	_col->Update();
	_weaponCol->Update();
	_actions[0]->Update();
	_sprites[0]->Update();
	_transform->Update();

	Gravity();
	Select();
}

void Player::Render()
{
	_transform->SetBuffer(0);
	_sprites[0]->SetCurClip(_actions[0]->GetCurClip());
	_sprites[0]->Render();
	_col->Render();
	_weaponCol->Render();
}

void Player::PostRender()
{
}

#pragma endregion

#pragma region Add Funtion
void Player::Select()
{
	LeftRight();
	Walk();
	Jump();
	Dash();
}
#pragma endregion

#pragma region Update Funtion


void Player::LeftRight()
{
	if (KEY_PRESS(VK_LEFT))
	{
		SetRight();
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		SetLeft();
	}
}


void Player::Jump()
{
	if (KEY_PRESS('C'))
	{
		_jumpPower = 600.0f;
	}
}

void Player::Walk()
{
	if (KEY_PRESS(VK_LEFT))
	{
		Vector2 movePos = Vector2(-500.0f, 0.0f);
		Move(movePos);
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		Vector2 movePos = Vector2(500.0f, 0.0f);
		Move(movePos);
	}
}

void Player::Dash()
{
	if (KEY_PRESS(VK_LSHIFT))
	{
		if (_isLeft == true)
		{
			SetSpeed(3.0f);
			Move(Vector2(-500.0f, 0.0f));
			SetSpeed(1.0f);
		}
		else
		{
			SetSpeed(3.0f);
			Move(Vector2(500.0f, 0.0f));
			SetSpeed(1.0f);
		}
	}
}



#pragma endregion

#pragma region NoUpdate

void Player::Gravity()
{
	_jumpPower -= 15;

	if (_jumpPower < -600.0f)
		_jumpPower = -600.0f;


	_col->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
}

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

	sprite->SetPS(ADD_PS(L"Shader/NonRedPS.hlsl"));
	_actions.push_back(action);
	_sprites.push_back(sprite);
}


void Player::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
	_isLeft = false;
}

void Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
	_isLeft = true;
}

#pragma endregion
