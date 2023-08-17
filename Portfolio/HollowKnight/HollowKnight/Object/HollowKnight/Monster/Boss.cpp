#include "framework.h"
#include "Boss.h"

Boss::Boss()
{
	_isLeft = true;
	_gravityCol = make_shared<RectCollider>(Vector2(20, 300));
	_jumpLine = make_shared<RectCollider>(Vector2(200, 40));
	_landLine = make_shared<RectCollider>(Vector2(200, 40));
	_col = make_shared<CircleCollider>(130);
	_weaponCol = make_shared<CircleCollider>(80);


	_transform->SetParent(_gravityCol->GetTransform());
	_jumpLine->SetPosition(Vector2(0, WIN_HEIGHT + 80));
	_landLine->SetPosition(Vector2(0, -85));
	_col->SetParent(_gravityCol->GetTransform());
	_weaponCol->SetParent(_col->GetTransform());
	_col->SetPosition(Vector2(0, 15));


	LocationFix(IDLE);
	CreateAction(L"Resource/Monster/Boss/BossIdle.png", "Resource/Monster/Boss/BossIdle.xml", "Idle", 
	Vector2((float)(620 * 1.2), (float)(393 * 1.2)), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossTurn.png", "Resource/Monster/Boss/BossTurn.xml", "Turn", 
	Vector2((float)(545 * 1.2), (float)(388 * 1.2)), Action::Type::END, std::bind(&Boss::TurnEvent, this));
	CreateAction(L"Resource/Monster/Boss/BossAttackReady.png", "Resource/Monster/Boss/BossAttackReady.xml", "AttackReady", 
	Vector2((float)(578 * 1.2), (float)(399 * 1.2)), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossAttack.png", "Resource/Monster/Boss/BossAttack.xml", "Attack",
	Vector2((float)(701 * 1.2), (float)(587 * 1.2)), Action::Type::END, std::bind(&Boss::AttackEvent, this));
	CreateAction(L"Resource/Monster/Boss/BossAttackFinish.png", "Resource/Monster/Boss/BossAttackFinish.xml", "AttackFinish", 
	Vector2((float)(647 * 1.2), (float)(572 * 1.2)), Action::Type::END, std::bind(&Boss::AttackEvent, this));
	CreateAction(L"Resource/Monster/Boss/BossJumpReady.png", "Resource/Monster/Boss/BossJumpReady.xml", "JumpReady", 
	Vector2((float)(605 * 1.2), (float)(381 * 1.2)), Action::Type::END, std::bind(&Boss::AttackEvent, this));
	CreateAction(L"Resource/Monster/Boss/BossJump.png", "Resource/Monster/Boss/BossJump.xml", "Jump", 
	Vector2((float)(598 * 1.2), (float)(335 * 1.2)), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossJumpAttack.png", "Resource/Monster/Boss/BossJumpAttack.xml", "JumpAttack",
	Vector2((float)(860 * 1.2), (float)(646 * 1.2)), Action::Type::END);
	CreateAction(L"Resource/Monster/Boss/BackStep.png", "Resource/Monster/Boss/BackStep.xml", "BackStep",
	Vector2((float)(500 * 1.2), (float)(613 * 1.2)), Action::Type::END, std::bind(&Boss::AttackEvent, this));
	CreateAction(L"Resource/Monster/Boss/JumpAttackToIdle.png", "Resource/Monster/Boss/JumpAttackToIdle.xml", "BackStep",
	Vector2((float)(600 * 1.2), (float)(443 * 1.2)), Action::Type::END, std::bind(&Boss::AttackEvent, this));
	CreateAction(L"Resource/Monster/Boss/GrogyAttack.png", "Resource/Monster/Boss/GrogyAttack.xml", "GrogyAttack",
	Vector2((float)(700 * 1.2), (float)(586 * 1.2)), Action::Type::END, std::bind(&Boss::AttackEvent, this));
	_actions[IDLE]->SetSpeed(0.35f);
	_actions[TURN]->SetSpeed(0.15f);
	_actions[ATTACK]->SetSpeed(0.07f);
	_actions[BACKSTEP]->SetSpeed(0.1f);
	_actions[JUMPTOIDLE]->SetSpeed(0.1f);
	_actions[GROGYATTACK]->SetSpeed(0.06f);
	//_actions[JUMPATTACK]->SetSpeed(1.0f);
	_gravityCol->SetPosition(Vector2(500, 0));
	_weaponCol->SetPosition(Vector2(-386, -108));
}

Boss::~Boss()
{
}

void Boss::Update()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	HighGravity(_gravityCol);
	_col->Update();
	if (_isAttack == true || _isGrogyAttack == true)
		_weaponCol->Update();
	_gravityCol->Update();
	_jumpLine->Update();
	_landLine->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	_jumpLine->SetPosition(Vector2(_gravityCol->GetTransform()->GetWorldPosition().x, _jumpLine->GetTransform()->GetWorldPosition().y));
	_landLine->SetPosition(Vector2(_gravityCol->GetTransform()->GetWorldPosition().x, _landLine->GetTransform()->GetWorldPosition().y));

	if (_curstate == JUMPATTACK)
		_jumpAttackTime += DELTA_TIME;

	if (_landLine->IsCollision(_col))
		_speed = 0.0f;
	
	if (_isWeaponActive == false)
		_weaponCol->SetRed();
	else
		_weaponCol->SetGreen();

	LocationFix(_curstate); // collider에 transform을 맞춰주는 함수
	DirFix();
	UnActiveIDle();
	Turn(); 
	AttackReadyEvent();
	ShakeEvent();
	JumpMove();
	Down();
	LandChange();
	JumpToIdle();
	if (_isWeaponMove == true)
		WeaponcolMove();
	if (KEY_DOWN('K'))
	{
		_actions[ATTACKREADY]->Play();
		LandAttackPattern();
	}

	if (KEY_DOWN('L'))
	{
		_actions[JUMPREADY]->Play();
		JumpAttackPattern();
	}

	if (KEY_DOWN('J'))
	{
		_actions[GROGYATTACK]->Play();
		AfterGroggyPattern();
	}
	//_transform->SetPosition(_location);
	//_weaponCol->SetPosition(_location);
	//_col->GetTransform()->SetAngle(_location.y);
	//_landLine->SetPosition(Vector2(0.0f, _location.y));
}

void Boss::Render()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();
	_col->Render();
	if(_isAttack == true || _isGrogyAttack == true)
		_weaponCol->Render();
	_jumpLine->Render();
	_landLine->Render();
	_gravityCol->Render();
}

void Boss::PostRender()
{
	ImGui::SliderFloat("Location.x", (float*)&_location.x, -600.0f, 600.0f);
	ImGui::SliderFloat("Location.y", (float*)&_location.y, 0.0f, 0.2f);
	ImGui::SliderInt("CurState", (int*)&_curstate, 0, 9);
	ImGui::Text("_isLeft : %d", _isLeft);
	ImGui::Text("_isTurn : %d", _isTurn);
	ImGui::Text("_isActive : %d", _isWeaponActive);
	ImGui::Text("count : %d", _weaponMove._count);
	ImGui::Text("_angle : %f", _weaponMove._weaponAngle);
	ImGui::Text("_Setangle : %f", _col->GetTransform()->GetAngle());
}

void Boss::Attack()
{
}

void Boss::SetState(State_Boss type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
}

void Boss::SetAndResetState(State_Boss type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
	_actions[_oldstate]->Reset();
}

void Boss::SetAndPlayState(State_Boss type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
}

void Boss::TotalUpdate(State_Boss type)
{
	LocationFix(type);
	_transform->Update();
	_actions[type]->Update();
	_sprites[type]->Update();
}

void Boss::Turn()
{
	_turnCoolTime += DELTA_TIME;

	if (_isTurn == true)
		return;
	if (_isAttack == true)
		return;
	if (_isGrogyAttack == true)
		return;
	if (_isJump == true)
		return;
	if (_turnCoolTime < 0.4f)
		return;

	_actions[TURN]->Reset();
	_actions[TURN]->Play();

	if (_isLeft == true)
	{
		if (_gravityCol->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x < 0)
		{
			_isTurn = true;
			_actions[TURN]->Update();
			if (_isLeft == false)
				SetLeft();
			else
				SetRight();
			TotalUpdate(TURN);
			SetState(TURN);
		}
		return;
	}

	if (_isLeft == false)
	{
		if (_gravityCol->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x > 0)
		{
			_isTurn = true;
			_actions[TURN]->Update();
			if (_isLeft == false)
				SetLeft();
			else
				SetRight();
			TotalUpdate(TURN);
			SetState(TURN);
		}
		return;
	}
}

void Boss::UnActiveIDle()
{
	if (_isJump == false && _isAttack == false && _isTurn == false && _isGrogyAttack == false)
	{
		TotalUpdate(IDLE);
		SetState(IDLE);
	}

}

void Boss::JumpMove()
{
	if (_isJump == true)
	{
		//if (_jumpPower < 0)
			//return;
		if (_isLeft == true)
		{
			_speed = (Vector2(_gravityCol->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_landPoint.x, 0.0f)).Length();
		}

		else
		{
			_speed = (Vector2(_gravityCol->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_landPoint.x, 0.0f)).Length();
		}

		if (_isLeft == true)
			_dir.x = -1;
		else
			_dir.x = 1;

		_gravityCol->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	}
}

void Boss::Down()
{
	if (_jumpLine->Block(_gravityCol))
	{
		if (_jumpPower < 120.0f)
			return;
		_jumpPower = 100.0f;
	}

	if (_jumpPower < -750.0f)
		_jumpPower = -1900.0f;
}

void Boss::LandChange()
{
	if (_isJump == true && _jumpPower < -1000)
	{
		if (_curstate == JUMPATTACK)
			return;

		_actions[JUMPATTACK]->Update();
		TotalUpdate(JUMPATTACK);
		SetState(JUMPATTACK);
		_actions[JUMPATTACK]->Play();
	}
}

void Boss::BackStep()
{
	if (_curstate != JUMPATTACK)
		return;
	_isJump = false;
	TotalUpdate(BACKSTEP);
	SetAndResetState(BACKSTEP);
}

void Boss::JumpToIdle()
{
	if (_jumpAttackTime > 0.2f)
	{
		_jumpAttackTime = 0.0f;
		BackStep();
	}
}

void Boss::WeaponcolMove()
{
	if (_weaponMove._weaponAngle < -2.3f)
	{
		_weaponMove._isPositive = true;
		_weaponMove._count += 1;
	}


	else if (_weaponMove._weaponAngle > 0.0f)
	{
		_weaponMove._isPositive = false;
		_weaponMove._count += 1;
	}

	if (_weaponMove._isPositive == true)
		_weaponMove._weaponAngle += 0.145;

	else if (_weaponMove._isPositive == false)
		_weaponMove._weaponAngle -= 0.145;

	if (_weaponMove._count >= 2)
		_isWeaponActive = false;

	_col->GetTransform()->SetAngle(_weaponMove._weaponAngle);
}

void Boss::TurnEvent()
{
	_actions[IDLE]->Update();
	_isTurn = false;
	_turnCoolTime = 0.0f;
}

void Boss::AttackReadyEvent()
{
	if (_curstate != ATTACKREADY)
		return;

	_chargeTime += DELTA_TIME;

	if (_chargeTime > 1.3f && _isGrogyAttack == false)
	{
		_col->GetTransform()->SetAngle(-2.29);
		_col->Update();
		_weaponMove._count = 0;
		_weaponMove._weaponAngle = -2.29;
		_isWeaponMove = true;
		_isWeaponActive = true;
		TotalUpdate(ATTACK);
		SetAndResetState(ATTACK);
		_chargeTime = 0.0f;
	}
	else if (_chargeTime > 1.3f && _isGrogyAttack == true)
	{
		TotalUpdate(GROGYATTACK);
		SetAndResetState(GROGYATTACK);
		_chargeTime = 0.0f;
	}
}

void Boss::AttackEvent()
{
	if (_curstate == ATTACK)
	{
		_shakeTiming = 0.0f;
		TotalUpdate(ATTACKFINISH);
		SetAndResetState(ATTACKFINISH);
		return;
	}

	if (_curstate == ATTACKFINISH)
	{
		TotalUpdate(IDLE);
		SetAndResetState(IDLE);
		_isWeaponMove = false;
		_isAttack = false;
		return;
	}

	if (_curstate == JUMPREADY)
	{
		if(_isLeft == true)
		_landPoint = _target.lock()->GetWorldPosition() + Vector2(300, 0);
		else
		_landPoint = _target.lock()->GetWorldPosition() - Vector2(300, 0);
		_isJump = true;
		TotalUpdate(JUMP);
		SetAndResetState(JUMP);
		_jumpPower = 1900.0f;
		return;
	}

	if (_curstate == BACKSTEP)
	{
		TotalUpdate(JUMPTOIDLE);
		SetAndResetState(JUMPTOIDLE);
		return;
	}

	if (_curstate == JUMPTOIDLE)
	{
		_isAttack = false;
		TotalUpdate(IDLE);
		SetAndResetState(IDLE);
		return;
	}

	if (_curstate == GROGYATTACK)
	{
		_isGrogyAttack = true;
		TotalUpdate(GROGYATTACK);
		if (_isLeft == true)
			SetRight();
		else
			SetLeft();
		_actions[GROGYATTACK]->Reset();
		SetAndPlayState(GROGYATTACK);
		return;
	}
}

void Boss::ShakeEvent()
{
	if (_curstate != ATTACK)
		return;
	_shakeTiming += DELTA_TIME;
	if (_shakeTiming > 0.22f)
	{
		CAMERA->ShakeStart(15.0f, 0.5f);
	}
}

void Boss::WeaponColEvent()
{

}

void Boss::LocationFix(State_Boss type)
{
	if (type == IDLE)
	{
		_transform->SetPosition(Vector2(68, 105));
	}

	if (type == TURN)
	{
		_transform->SetPosition(Vector2(0, 100));
	}

	if (type == ATTACKREADY)
	{
		_transform->SetPosition(Vector2(140, 90));
	}

	if (type == ATTACK)
	{
		_transform->SetPosition(Vector2(-98, 193));
	}

	if (type == ATTACKFINISH)
	{
		_transform->SetPosition(Vector2(-33, 193));
	}

	if (type == JUMPREADY)
	{
		_transform->SetPosition(Vector2(63, 98));
	}

	if (type == JUMP)
	{
		_transform->SetPosition(Vector2(160, 70));
	}

	if (type == JUMPATTACK)
	{
		_transform->SetPosition(Vector2(-120, 250));
	}

	if (type == BACKSTEP)
	{
		_transform->SetPosition(Vector2(107, 206));
	}

	if (type == JUMPTOIDLE)
	{
		_transform->SetPosition(Vector2(25, 115));
	}

	if (type == GROGYATTACK)
	{
		_transform->SetPosition(Vector2(-93, 198));
	}
}

void Boss::DirFix()
{
	if (_isJump == false && _dir.Length() != 0)
	{
		_dir = Vector2(_target.lock()->GetWorldPosition().x, 0.0f) - Vector2(_gravityCol->GetTransform()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NomalVector2();
	}
}

void Boss::LandAttackPattern()
{
	_isAttack = true;
	_col->GetTransform()->SetAngle(-3.7f);
	_weaponMove._weaponAngle = -3.7f;
	TotalUpdate(ATTACKREADY);
	SetState(ATTACKREADY);
}

void Boss::JumpAttackPattern()
{
	_isAttack = true;
	TotalUpdate(JUMPREADY);
	SetState(JUMPREADY);
}

void Boss::AfterGroggyPattern()
{
	_isGrogyAttack = true;
	TotalUpdate(ATTACKREADY);
	_actions[ATTACKREADY]->Reset();
	SetAndPlayState(ATTACKREADY);
}

void Boss::SetLeft()
{
	_actions[_curstate]->Update();
	_gravityCol->SetScale(Vector2(1, 1));
	_isLeft = true;
}

void Boss::SetRight()
{
	_actions[_curstate]->Update();
	_gravityCol->SetScale(Vector2(-1, 1));
	_isLeft = false;
}
