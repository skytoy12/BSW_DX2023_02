#include "framework.h"
#include "Boss.h"

Boss::Boss()
{
#pragma region collider, transform등 생성 및 초기설정
	_isLeft = true;
	_gravityCol = make_shared<RectCollider>(Vector2(20, 300));
	_jumpLine = make_shared<RectCollider>(Vector2(200, 40));
	_landLine = make_shared<RectCollider>(Vector2(200, 40));
	_col = make_shared<CircleCollider>(150);
	_weaponCol = make_shared<CircleCollider>(80);


	_transform->SetParent(_gravityCol->GetTransform());
	_jumpLine->SetPosition(Vector2(0, WIN_HEIGHT + 80));
	_landLine->SetPosition(Vector2(0, -85));
	_col->SetParent(_gravityCol->GetTransform());
	_weaponCol->SetParent(_col->GetTransform());
	_col->SetPosition(Vector2(0, 15));

	_gravityCol->SetPosition(Vector2(500, 0));
	_weaponCol->SetPosition(Vector2(-386, -108));
#pragma endregion



#pragma region Action제작 및 초기설정
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
	CreateAction(L"Resource/Monster/Boss/GrogyStart.png", "Resource/Monster/Boss/GrogyStart.xml", "GrogyStart",
	Vector2((float)(760 * 1.2), (float)(510 * 1.2)), Action::Type::END, std::bind(&Boss::GrogyEvent, this));
	CreateAction(L"Resource/Monster/Boss/GrogyRolling.png", "Resource/Monster/Boss/GrogyRolling.xml", "GrogyRolling",
	Vector2((float)(753 * 1.2), (float)(512 * 1.2)), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/Grogy.png", "Resource/Monster/Boss/Grogy.xml", "Grogy",
	Vector2((float)(412 * 1.2), (float)(467 * 1.2)), Action::Type::END);
	CreateAction(L"Resource/Monster/Boss/GrogyHead.png", "Resource/Monster/Boss/GrogyHead.xml", "GrogyHead",
	Vector2((float)(392 * 1.2), (float)(451 * 1.2)), Action::Type::END);

#pragma endregion

#pragma region Action 설정

	SetActionSpeed(IDLE, 0.35f);
	SetActionSpeed(TURN, 0.15f);
	SetActionSpeed(ATTACK, 0.07f);
	SetActionSpeed(BACKSTEP, 0.1f);
	SetActionSpeed(JUMPTOIDLE, 0.1f);
	SetActionSpeed(GROGYATTACK, 0.08f);
	SetActionSpeed(GROGYHEAD, 0.15f);
	//_actions[JUMPATTACK]->SetSpeed(1.0f);

#pragma endregion
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
	GrogyRollingFinish();
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

	if (KEY_DOWN('H'))
	{
		_actions[GROGYSTART]->Play();
		Grogy();
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
	ImGui::SliderFloat("Location.y", (float*)&_location.y, -600.0f, 600.0f);
	ImGui::SliderInt("CurState", (int*)&_curstate, 0, 14);
	ImGui::Text("_isLeft : %d", _isLeft);
	ImGui::Text("_isTurn : %d", _isTurn);
	ImGui::Text("_isJump : %d", _isJump);
	ImGui::Text("_isJumpAttack : %d", _isJumpAttack);
	ImGui::Text("_isAttack : %d", _isAttack);
	ImGui::Text("_isGrogyAttack : %d", _isGrogyAttack);
	ImGui::Text("_isreturn : %d", _isreturn);
	ImGui::Text("_isActive : %d", _isWeaponActive);
	ImGui::Text("_isGrogy : %d", _isGrogy);
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

	_isreturn = Return();

	if (_isreturn == 1)
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
	if (Return() != 1)
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

int Boss::Return()
{
	if (_isTurn == true)
		return 1;
	if (_isAttack == true)
		return 1;
	if (_isGrogyAttack == true)
		return 1;
	if (_isJumpAttack == true)
		return 1;
	if (_isJump == true)
		return 1;
	if (_isJustJump == true)
		return 1;
	if (_isGrogy == true)
		return 1;

	return 0;
}

void Boss::GrogyEvent()
{
	if (_isGrogy == false)
		return;

	if (_curstate == GROGYSTART)
	{
		TotalUpdate(GROGYROLLING);
		SetAndResetState(GROGYROLLING);
		return;
	}


	if (_curstate == GROGY)
	{
		TotalUpdate(GROGYHEAD);
		SetAndResetState(GROGYHEAD);
		return;
	}
}

void Boss::LandChange()
{
	if (_isJump == true && _jumpPower < -1000)
	{
		if (_curstate == JUMPATTACK)
			return;
		_col->GetTransform()->SetAngle(0.0f);
		_weaponMove._weaponAngle = 0.0f;
		_weaponMove._speed = 0.0f;
		_actions[JUMPATTACK]->Update();
		_isWeaponActive = true;
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
	_isWeaponActive = false;
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
		_weaponMove._weaponAngle += _weaponMove._speed;

	else if (_weaponMove._isPositive == false)
		_weaponMove._weaponAngle -= _weaponMove._speed;

	if (_weaponMove._count >= 2 && _isGrogyAttack == false)
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
		_weaponMove._weaponAngle = -2.29f;
		_weaponMove._speed = 0.145f;
		_isWeaponMove = true;
		_isWeaponActive = true;
		TotalUpdate(ATTACK);
		SetAndResetState(ATTACK);
		_chargeTime = 0.0f;
	}
	else if (_chargeTime > 1.3f && _isGrogyAttack == true)
	{
		_col->GetTransform()->SetAngle(-2.29f);
		_col->Update();
		_weaponMove._count = 0;
		_weaponMove._weaponAngle = -2.29;
		_weaponMove._speed = 0.45f;
		_isWeaponMove = true;
		_isWeaponActive = true;
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
		_isJumpAttack = false;
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

		if (_weaponMove._count < 26)
		{
			_actions[GROGYATTACK]->Reset();
			SetAndPlayState(GROGYATTACK);
			return;
		}
		else
		{
			_isGrogyAttack = false;
			_weaponMove._speed = 0.0f;
			_weaponMove._count = 0;
			TotalUpdate(IDLE);
			SetAndResetState(IDLE);
			return;
		}
	}
}

void Boss::ShakeEvent()
{
	LandAttackShakeEvent();
	GrogyAttackShakeEvent();
	JumpAttackShakeEvent();
}


void Boss::LandAttackShakeEvent()
{
	if (_curstate != ATTACK)
		return;
	_shakeTiming += DELTA_TIME;
	if (_shakeTiming > 0.22f)
	{
		CAMERA->ShakeStart(15.0f, 0.7f);
	}
}

void Boss::GrogyEndEvent()
{
	if (_weaponMove._count < 26)
		return;

}

void Boss::GrogyAttackShakeEvent()
{
	if (_curstate != GROGYATTACK)
		return;
	_shakeTiming += DELTA_TIME;
	if (_shakeTiming > 0.22f)
	{
		CAMERA->ShakeStart(15.0f, 0.5f);
	}
}

void Boss::JumpAttackShakeEvent()
{
	if (_curstate != JUMPATTACK)
		return;
	CAMERA->ShakeStart(15.0f, 0.5f);
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

	if (type == GROGYSTART)
	{
		_transform->SetPosition(Vector2(-20, 110));
	}

	if (type == GROGYROLLING)
	{
		_transform->SetPosition(Vector2(-33, 155));
	}

	if (type == GROGY)
	{
		_transform->SetPosition(Vector2(0, 150));
	}

	if (type == GROGYHEAD)
	{
		_transform->SetPosition(Vector2(0, 135));
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

void Boss::AllStop()
{
	_isJump = false;
	_isJustJump = false;
	_isAttack = false;
	_isJumpAttack = false;
	_isGrogyAttack = false;
	_isTurn = false;
	_isWeaponMove = false;
	_isWeaponActive = false;
}



void Boss::LandAttackPattern()
{

	_isreturn = Return();

	if (_isreturn == 1)
		return;
	_isAttack = true;
	_col->GetTransform()->SetAngle(-3.7f);
	_weaponMove._weaponAngle = -3.7f;
	TotalUpdate(ATTACKREADY);
	SetState(ATTACKREADY);
}


void Boss::JumpAttackPattern()
{

	_isreturn = Return();

	if (_isreturn == 1)
		return;
	_isJumpAttack = true;
	TotalUpdate(JUMPREADY);
	SetState(JUMPREADY);
}

void Boss::AfterGroggyPattern()
{
	_isreturn = Return();

	if (_isreturn == 1)
		return;
	_isGrogyAttack = true;
	_col->GetTransform()->SetAngle(-3.7f);
	_weaponMove._weaponAngle = -3.7f;
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

void Boss::Grogy()
{
	if (_isGrogy == true)
		return;
	_isGrogy = true;
	AllStop();
	TotalUpdate(GROGYSTART);
	SetAndResetState(GROGYSTART);
}
void Boss::SetActionSpeed(State_Boss type, float speed)
{
	_actions[type]->SetSpeed(speed);
}

void Boss::GrogyRollingFinish()
{
	if (_curstate == GROGYROLLING)
	{
		_rollingTime += DELTA_TIME;

		if (_rollingTime < 2.0f)
			return;
		TotalUpdate(GROGY);
		SetAndResetState(GROGY);
		_rollingTime = 0.0f;
	}

	if (_curstate == GROGY)
	{
		_GrogyStopTime += DELTA_TIME;
		if (_GrogyStopTime < 1.8f)
			return;
		TotalUpdate(GROGYHEAD);
		SetAndResetState(GROGYHEAD);
		_rollingTime = 0.0f;
	}
}
