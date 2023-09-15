#include "framework.h"
#include "Player.h"
#include "Bullet.h"
#include "ChargeEffect.h"
#include "../Monster/_Monster.h"
#include "../_Terrain/Wall.h"

class Wall;

using namespace tinyxml2;

#pragma region Player

Player::Player()
{
#pragma region Create Base
	_col = make_shared<RectCollider>(Vector2(50, 100));
	_weaponCol = make_shared<RectCollider>(Vector2(120, 70));
	_dashCol = make_shared<CircleCollider>(10);
	_distanceCol = make_shared<RectCollider>(Vector2(250, 75));
	_transform = make_shared<Transform>();
	_bullet = make_shared<Bullet>();
	_bulletCol = make_shared<CircleCollider>(50);
	_effect = make_shared<ChargeEffect>();
	_frame = make_shared<HPFrame>();
	_orb = make_shared<SoulOrb>();
	for (int i = 0; i < 10; i++)
	{
		shared_ptr<HPBar> hp = make_shared<HPBar>();
		_hpBars.push_back(hp);
	}
#pragma endregion
#pragma region CreateAction
	CreateAction(L"Resource/Player/Idle.png", "Resource/Player/Idle.xml", "Idle", 
	Vector2(61, 130), Action::Type::LOOP);
	CreateAction(L"Resource/Player/RunStart.png", "Resource/Player/RunStart.xml", "RunStart", 
	Vector2(86, 130), Action::Type::END, std::bind(&Player::EndEvent, this));
	CreateAction(L"Resource/Player/Running.png", "Resource/Player/Running.xml", "Running", 
	Vector2(86, 130), Action::Type::LOOP);
	CreateAction(L"Resource/Player/Dash.png", "Resource/Player/Dash.xml", "Dash", 
	Vector2(192, 117), Action::Type::END, std::bind(&Player::EndEvent, this));
	CreateAction(L"Resource/Player/DNSlash.png", "Resource/Player/DNSlash.xml", "Slash", 
	Vector2(283, 136), Action::Type::END, std::bind(&Player::EndEvent, this));
	CreateAction(L"Resource/Player/Charge.png", "Resource/Player/Charge.xml", "Charge", 
	Vector2(114, 127), Action::Type::LOOP);
	CreateAction(L"Resource/Player/Recoil.png", "Resource/Player/Recoil.xml", "Recoil", 
	Vector2(124, 137), Action::Type::END, std::bind(&Player::UnbeatableToIdle, this));
	CreateAction(L"Resource/Player/Death.png", "Resource/Player/Death.xml", "Death",
	Vector2(116, 131), Action::Type::END, std::bind(&Player::EndEvent, this));
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
	_distanceCol->SetParent(_col->GetTransform());
	_distanceCol->SetPosition(Vector2(125, 10));
	_transform->SetPosition(Vector2(0, 18));
	_bulletCol->SetParent(_bullet->GetCollider()->GetTransform());
	_effect->GetTransform()->SetParent(_col->GetTransform());
	_actions[DASH]->SetSpeed(0.05f);
	_actions[SLASH]->SetSpeed(0.03f);

	_frame->SetPosition(Vector2(-410, 265));
	_orb->SetPosition(Vector2(-537, 255));
	_orb->SetScale(Vector2(0.7f, 0.7f));
	for (int i = 0; i < 10; i++)
	{
		_hpBars[i]->SetPosition(Vector2(-470 + (30 * i), 235));
	}
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



	if (_isDeath == true)
		return;

	HPBarActive();

	if (_isAttack == false)
	{
		_isWeaponActive = false;
		ActiveOn(false);
	}
	_col->Update();
	if (_isAttack == true)
		_weaponCol->Update();
	_dashCol->Update();
	_distanceCol->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_transform->Update();
	_bullet->Update();
	_effect->Update();

	//////UI/////////////
	_frame->Update();
	_orb->Update();	
	for (auto hp : _hpBars)
	{
		hp->Update();
	}
	SoulOrbRatio();
	/////////////////////

	if (_isBulletActive == false)
	{
		_bullet->_isAttack = false;
	}

	if (_bullet->_isActive == true)
		_bulletCol->Update();

	if (_isWeaponActive == true)
		_weaponCol->SetGreen();
	else
		_weaponCol->SetBlue();

	Time();
	if (_isAlive == true)
	{
		CoolTime();
		if (_isDash == false)
			Gravity();
		if (_hitmotion == false)
			Select();
		if (_jumpPower < -600.0f)
			_isJump = true;
		HitKnockBack();
	}

}

void Player::Render()
{
	if (_isDeath == true)
		return;

	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();
	_col->Render();
	_distanceCol->Render();
	if(_isAttack == true)
		_weaponCol->Render();
	_bullet->Render();
	_effect->Render();
	if(_bullet->_isActive == true)
		_bulletCol->Render();


}

void Player::PostRender()
{
	//////UI/////////////
	_frame->PostRender();
	_orb->PostRender();
	for (auto hp : _hpBars)
	{
		hp->PostRender();
	}

	/////////////////////
	// 
	

	ImGui::Text("jumpP : %f", _jumpPower);
	ImGui::Text("_dash : %f", _dash);
	//ImGui::SliderFloat("Location.x", (float*)&_test.x, -WIN_WIDTH * 0.5f, +WIN_WIDTH * 0.5f);
    //ImGui::SliderFloat("Location.y", (float*)&_test.y, -WIN_HEIGHT * 0.5f, +WIN_HEIGHT * 0.5f);
    //ImGui::SliderFloat("scale", (float*)&_testfloat, 0.0f, 2.0f);

	//ImGui::Text("hp1 : %d", _hpBars[0]->GetState());
	//ImGui::Text("hp2 : %d", _hpBars[1]->GetState());
	//ImGui::Text("hp3 : %d", _hpBars[2]->GetState());
	//ImGui::Text("hp4 : %d", _hpBars[3]->GetState());
	//ImGui::Text("hp5 : %d", _hpBars[4]->GetState());
	//ImGui::Text("hp6 : %d", _hpBars[5]->GetState());
	//ImGui::Text("hp7 : %d", _hpBars[6]->GetState());

	//ImGui::Text("_isWeaponAct : %d", _isWeaponActive);
	//ImGui::Text("_isAttack : %d", _isAttack);
	//ImGui::Text("Death : %d", _isDeath);
	//ImGui::Text("state : %d", _curstate);
	//ImGui::Text("HP : %d", _hp);

	//ImGui::Text("_isBulletActive : %d", _isBulletActive);
	//ImGui::Text("_isActiveB : %d", _bullet->_isActive);
	//ImGui::Text("_isAttackB : %d", _bullet->_isAttack);


	//ImGui::Text("world.x : %.1f, world.y : %.1f", _col->GetTransform()->GetWorldPosition().x, _col->GetTransform()->GetWorldPosition().y);
	//ImGui::Text("Camera.x : %.1f, Camera.y : %.1f", CAMERA->GetOringin().x, CAMERA->GetOringin().y);
	//ImGui::Text("Random.x : %.1f, Random.y : %.1f", CAMERA->GetRandomPos().x, CAMERA->GetRandomPos().y);
}

#pragma endregion

#pragma region Add Funtion
void Player::Select()
{
	LeftRight();
	Walk();
	Jump();
	//Dash();
	Attack();
	if(_bulletCoolTime > 2.9f)
		ChargeAndFire();
	if (KEY_DOWN(VK_F4))
	{
		AllStop();
		SetAndResetState(DEATH);
	}

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

	if (_isUnbeatable == true)
		return;
	if (_isCanDash == 0)
	{
		_dash = 250.0f;
		return;
	}

	{
		_isDash = true;
		_jumpPower = 0;

		if (_isLeft == true)
		{
			SetAndResetState(DASH);
			SetSpeed(3.0f);
			DashMove(Vector2(-_dash, 0.0f));
			SetSpeed(1.0f);
			EFFECT_LPLAY("Dash", _dashCol->GetTransform()->GetWorldPosition());
		}
		else
		{
			SetAndResetState(DASH);
			SetSpeed(3.0f);
			DashMove(Vector2(_dash, 0.0f));
			SetSpeed(1.0f);
			EFFECT_RPLAY("Dash", _dashCol->GetTransform()->GetWorldPosition());
		}
		_dash = 250.0f;
		_isCanDash = 0;
	}
	//if (KEY_DOWN(VK_LSHIFT))
	//{
	//	_isDash = true;
	//	_jumpPower = 0;

	//	if (_isLeft == true)
	//	{
	//		SetAndResetState(DASH);
	//		SetSpeed(3.0f);
	//		DashMove(Vector2(-_dash, 0.0f));
	//		SetSpeed(1.0f);
	//		EFFECT_LPLAY("Dash", _dashCol->GetTransform()->GetWorldPosition());
	//	}
	//	else
	//	{
	//		SetAndResetState(DASH);
	//		SetSpeed(3.0f);
	//		DashMove(Vector2(_dash, 0.0f));
	//		SetSpeed(1.0f);
	//		EFFECT_RPLAY("Dash", _dashCol->GetTransform()->GetWorldPosition());
	//	}
	//	_dash = 250.0f;
	//}
}

void Player::CutDash(shared_ptr<Wall> wall)
{
#define WallWP wall->GetCollider()->GetTransform()->GetWorldPosition()
#define WP _col->GetTransform()->GetWorldPosition()

	if (KEY_DOWN(VK_LSHIFT))
	{
		_isDashCol = true;

		if (_distanceCol->IsCollision(wall->GetCollider()) && _isDashCol == true)
		{
			float distance = abs(WP.x - WallWP.x);
			float Sum = 25.0f + (wall->GetSize().x / 2);

			_dash = abs(Sum - distance);
			_isDashCol = false;
			return;
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
		ActiveOn(true);
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
	if (_curMp < 51)
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
		if (_chargeTime < 0.3f)
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
			_isBulletActive = true;
			_bullet->_isAttack = true;
			_curMp -= 50;
		}
		else
		{
			_chargeTime = 0.0f;
			_bulletCoolTime = 0.0f;
			_bullet->Update();
			_bullet->Shoot(_col->GetTransform()->GetWorldPosition(), Vector2(-1, 0));
			_isBulletActive = true;
			_bullet->_isAttack = true;
			_curMp -= 50;
		}

		_isChargeAndFire = false;
	}
}

void Player::ActiveOn(bool value)
{
	_isWeaponActiveB = value;
	_isWeaponActiveF = value;
	_isWeaponActiveJ = value;
	_isWeaponActiveR = value;
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
		_isDeath = true;
		return;
	}
}

#pragma endregion

#pragma region NoUpdate

void Player::Gravity()
{
	_jumpPower -= 15;

	if (_jumpPower < -610.0f)
		_jumpPower = -610.0f;


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



void Player::AllStop()
{
	_isWeaponActiveB = false;
	_isWeaponActiveF = false;
	_isWeaponActiveJ = false;
	_isWeaponActiveR = false;
	_isJump = false;
	_isAttack = false;
	_isWeaponActive = false;
	_isDash = false;
	_isChargeAndFire = false;
	_effect->_isActive = false;
}

void Player::HPBarActive()
{
	for (int i = 0; i < 10; i++)
	{
		if (i + 1 > _maxHp)
			_hpBars[i]->SetState(HPBar::HPState::NONE);
		else if (i + 1 > _hp && i + 1 <= _maxHp)
			_hpBars[i]->SetState(HPBar::HPState::BROKEN);
		else if (i + 1 <= _hp)
			_hpBars[i]->SetState(HPBar::HPState::FULL);
	}
}

void Player::MPRecovery()
{
	_curMp += 20;
	if (_curMp > _maxMp)
		_curMp = _maxMp;
}

void Player::SoulOrbRatio()
{
	_orb->GetRatioBuffer()->_data.cur = _curMp;
	_orb->GetRatioBuffer()->_data.max = _maxMp;
}

void Player::Hitted()
{
	if (_isUnbeatable == true)
		return;
	if (_isAlive == false)
		return;
	AllStop();
	_isUnbeatable = true;

	_jumpPower = 300.0f;

	_KBspeed = 600;
	_hp -= 1;
	if (_hp <= 0)
		_hp = 0;

	if (_hp == 0)
	{
		_isAlive = false;
		_isUnbeatable = false;
		SetAndResetState(DEATH);
		return;
	}

	_isKnockBackTime = true;
	_hitmotion = true;
	SetAndResetState(RECOIL);
}

void Player::HitKnockBack()
{
	if (_isKnockBackTime == true)
		_col->GetTransform()->AddVector2(_KBdir * _KBspeed * DELTA_TIME);

	if (_isKnockBackTime > 0.1f && _isKnockBackTime < 0.2f)
		_jumpPower = -400.0f;
}

void Player::UnbeatableToIdle()
{
	_hitmotion = false;
	SetAndResetState(IDLE);
}

void Player::Time()
{
	if (_isKnockBackTime == true)
		_knockBackTime += DELTA_TIME;
	if (_isUnbeatable == true)
		_unbeatableTime += DELTA_TIME;

	if (_knockBackTime > 0.5f)
	{
		_isKnockBackTime = false;
		_knockBackTime = 0.0f;
	}

	if (_unbeatableTime > 1.0f)
	{
		_isUnbeatable = false;
		_unbeatableTime = 0.0f;
	}
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

void Player::SetCanDash(bool value)
{
	if (value == true)
		_isCanDash = 1;
	else
		_isCanDash = 0;
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
