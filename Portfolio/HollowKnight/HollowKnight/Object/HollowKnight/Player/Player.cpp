#include "framework.h"
#include "Player.h"
#include "Bullet.h"
#include "ChargeEffect.h"
#include "../Monster/_Monster.h"

using namespace tinyxml2;

#pragma region Player

Player::Player()
{
#pragma region Create Base
	_col = make_shared<RectCollider>(Vector2(50, 100));
	_weaponCol = make_shared<RectCollider>(Vector2(120, 70));
	_dashCol = make_shared<CircleCollider>(10);
	_transform = make_shared<Transform>();
	_bullet = make_shared<Bullet>();
	_effect = make_shared<ChargeEffect>();
#pragma endregion
#pragma region CreateAction
	CreateAction(L"Resource/Player/Idle.png", "Resource/Player/Idle.xml", "Idle", Vector2(61, 130), Action::Type::LOOP);
	CreateAction(L"Resource/Player/RunStart.png", "Resource/Player/RunStart.xml", "RunStart", Vector2(86, 130), Action::Type::END, std::bind(&Player::EndEvent, this));
	CreateAction(L"Resource/Player/Running.png", "Resource/Player/Running.xml", "Running", Vector2(86, 130), Action::Type::LOOP);
	CreateAction(L"Resource/Player/Dash.png", "Resource/Player/Dash.xml", "Dash", Vector2(192, 117), Action::Type::END, std::bind(&Player::EndEvent, this));
	_actions[DASH]->SetSpeed(0.05f);
	CreateAction(L"Resource/Player/DNSlash.png", "Resource/Player/DNSlash.xml", "Slash", Vector2(283, 136), Action::Type::END, std::bind(&Player::EndEvent, this));
	_actions[SLASH]->SetSpeed(0.03f);
	CreateAction(L"Resource/Player/Charge.png", "Resource/Player/Charge.xml", "Charge", Vector2(114, 127), Action::Type::LOOP);
	CreateAction(L"Resource/Player/Death.png", "Resource/Player/Death.xml", "Death", Vector2(116, 131), Action::Type::END, std::bind(&Player::EndEvent, this));
#pragma endregion

#pragma region CREAT EFFECT
	EffectManager::GetInstance()->AddEffect("Dash", L"Resource/Effect/DashEffect.png", Vector2(1, 8), Vector2(402, 188));
	EffectManager::GetInstance()->AddEffect("Slash", L"Resource/Effect/SlashEffect.png", Vector2(6, 1), Vector2(157, 114));
#pragma endregion

#pragma region Setting
	_transform->SetParent(_col->GetTransform());
	_weaponCol->GetTransform()->SetParent(_col->GetTransform());
	_weaponCol->SetPosition(Vector2(80, -5));
	_dashCol->SetParent(_col->GetTransform());
	_dashCol->SetPosition(Vector2(0, -15));
	_transform->SetPosition(Vector2(0, 18));
	_effect->GetTransform()->SetParent(_col->GetTransform());
#pragma endregion

#pragma region TEST
	//SetState(DASH);
#pragma endregion
}

Player::~Player()
{
}

void Player::Update()
{
	if (KEY_DOWN(VK_F3))
	{
		SetAndResetState(IDLE);
		_isAlive = true;
	}

	if (_isAlive == false)
		return;

	_col->Update();
	if (_isAttack == true)
		_weaponCol->Update();
	_dashCol->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_transform->Update();
	_bullet->Update();
	_effect->Update();

	if (_isWeaponActive == true)
		_weaponCol->SetGreen();
	else
		_weaponCol->SetRed();

	CoolTime();
	if(_isDash == false)
		Gravity();
	Select();
}

void Player::Render()
{
	if (_isAlive == false)
		return;

	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();
	_col->Render();
	if(_isAttack == true)
		_weaponCol->Render();
	_bullet->Render();
	_effect->Render();
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
	Attack();
	if(_bulletCoolTime > 2.9f)
		ChargeAndFire();
	if (KEY_DOWN(VK_F4))
		SetAndResetState(DEATH);
}

#pragma endregion

#pragma region Update Funtion


void Player::LeftRight()
{

	if (_isDash == true)
		return;

	if (_isAttack == true)
		return;

	if (_isChargeAndFire == true)
		return;

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
	if (_isJump == true)
		return;

	if (_isDash == true)
		return;

	if (_isAttack == true)
		return;

	if (KEY_PRESS('C'))
	{
		_isJump = true;
		_jumpPower = 600.0f;
	}
}

void Player::Walk()
{
	if (_isDash == true)
		return;

	if (_isAttack == true)
		return;

	if (_isChargeAndFire == true)
		return;

	if (KEY_PRESS(VK_LEFT))
	{
		if (_curstate != RUNNING && _curstate != RUNSTART)
			SetAndResetState(RUNSTART);
		Vector2 movePos = Vector2(-500.0f, 0.0f);
		Move(movePos);
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		if (_curstate != RUNNING && _curstate != RUNSTART)
			SetAndResetState(RUNSTART);
		Vector2 movePos = Vector2(500.0f, 0.0f);
		Move(movePos);
	}

	if (KEY_UP(VK_LEFT))
	{
		SetAndResetState(IDLE);
	}

	if (KEY_UP(VK_RIGHT))
	{
		SetAndResetState(IDLE);
	}
}

void Player::Dash()
{
	if (_isDash == true)
		return;

	if (_isAttack == true)
		return;

	if (_isChargeAndFire == true)
		return;


	if (KEY_DOWN(VK_LSHIFT))
	{
		_isDash = true;
		_jumpPower = 0;

		if (_isLeft == true)
		{
			SetAndResetState(DASH);
			SetSpeed(3.0f);
			Move(Vector2(-5000.0f, 0.0f));
			SetSpeed(1.0f);
			EFFECT_LPLAY("Dash", _dashCol->GetTransform()->GetWorldPosition());
		}
		else
		{
			SetAndResetState(DASH);
			SetSpeed(3.0f);
			Move(Vector2(5000.0f, 0.0f));
			SetSpeed(1.0f);
			EFFECT_RPLAY("Dash", _dashCol->GetTransform()->GetWorldPosition());
		}
	}
}

void Player::Attack()
{
	if (_isAttack == true)
		return;
	if (_isDash == true)
		return;

	if (KEY_PRESS('X'))
	{
		_weaponCol->Update();
		_isAttack = true;
		_isWeaponActive = true;
		SetAndResetState(SLASH);
		if(_isLeft == true)
			EFFECT_RPLAY("Slash", _weaponCol->GetTransform()->GetWorldPosition() + Vector2(-10, 0));
		else
			EFFECT_LPLAY("Slash", _weaponCol->GetTransform()->GetWorldPosition() + Vector2(10, 0));
	}
}

void Player::ChargeAndFire()
{
	if (_isDash == true)
		return;
	if (_isAttack == true)
		return;

	if (KEY_DOWN('Z'))
	{
		_effect->_isActive = true;
		_effect->Update();
		_effect->Play();
		_isChargeAndFire = true;
	}
	if (KEY_PRESS('Z'))
	{
		_effect->_isActive = true;
		SetAndResetState(CHARGE);
		_chargeTime += DELTA_TIME;
	}

	if (KEY_UP('Z'))
	{
		_effect->Reset();
		_effect->_isActive = false;
		if (_chargeTime < 1.0f)
		{
			_chargeTime = 0.0f;
			SetAndResetState(IDLE);
			_isChargeAndFire = false;
			return;
		}

		SetAndResetState(SLASH);
		if (_bullet->_isActive == true)
		{
			_isChargeAndFire = false;
			return;
		}


		if (_isLeft == false)
		{
			_chargeTime = 0.0f;
			_bulletCoolTime = 0.0f;
			_bullet->Update();
			_bullet->Shoot(_col->GetTransform()->GetWorldPosition());
		}
		else
		{
			_chargeTime = 0.0f;
			_bulletCoolTime = 0.0f;
			_bullet->Update();
			_bullet->Shoot(_col->GetTransform()->GetWorldPosition(), Vector2(-1, 0));
		}

		_isChargeAndFire = false;
	}
}

void Player::EndEvent()
{
	if (_curstate == RUNSTART)
	{
		SetAndResetState(RUNNING);
		return;
	}

	if (_curstate == DASH)
	{
		SetAndResetState(IDLE);
		_isDash = false;
		return;
	}

	if (_curstate == SLASH)
	{
		SetAndResetState(IDLE);
		_isAttack = false;
		_isChargeAndFire = false;
		return;
	}

	if (_curstate == DEATH)
	{
		_isAlive = false;
		return;
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

void Player::CoolTime()
{
	_bulletCoolTime += DELTA_TIME;
	if (_bulletCoolTime > 3.0f)
		_bulletCoolTime = 3.0f;
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
	action->Update();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	sprite->SetPS(ADD_PS(L"Shader/NonRedPS.hlsl"));
	sprite->Update();
	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Player::SetEnemy(shared_ptr<class Monster> enemy)
{
	_enemies.push_back(enemy);
}


void Player::SetState(State_Player type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
}

void Player::SetAndResetState(State_Player type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
	_actions[_oldstate]->Reset();
}

void Player::SetLeft()
{
	//for (auto sprite : _sprites)
	//	sprite->SetLeft();
	_col->SetScale(Vector2(1, 1));
	_isLeft = false;
}

void Player::SetRight()
{
	//for (auto sprite : _sprites)
	//	sprite->SetRight();
	_col->SetScale(Vector2(-1, 1));
	_isLeft = true;
}

#pragma endregion
