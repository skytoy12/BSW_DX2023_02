#include "framework.h"
#include "Boss.h"

Boss::Boss()
{
	_isLeft = true;
	_gravityCol = make_shared<RectCollider>(Vector2(20, 260));
	_col = make_shared<CircleCollider>(130);
	_transform->SetParent(_gravityCol->GetTransform());
	_col->SetParent(_gravityCol->GetTransform());
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
	Vector2((float)(605 * 1.2), (float)(381 * 1.2)), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossJump.png", "Resource/Monster/Boss/BossJump.xml", "Jump", 
	Vector2((float)(598 * 1.2), (float)(335 * 1.2)), Action::Type::LOOP);
	_actions[IDLE]->SetSpeed(0.35f);
	_actions[TURN]->SetSpeed(0.15f);
	_actions[ATTACK]->SetSpeed(0.07f);
	//_actions[ATTACKFINISH]->SetSpeed(1.0f);
	_gravityCol->SetPosition(Vector2(500, 0));
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

	Gravity(_gravityCol);
	_col->Update();
	_gravityCol->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();


	LocationFix(_curstate); // collider에 transform을 맞춰주는 함수
	DirFix();
	UnActiveIDle();
	Turn(); 
	AttackReadyEvent();
	ShakeEvent();
	if (KEY_DOWN('K'))
	{
		_actions[ATTACKREADY]->Play();
		LandAttackPattern();
	}
	//_transform->SetPosition(_location);
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
	_gravityCol->Render();
}

void Boss::PostRender()
{
	ImGui::SliderFloat("Location.x", (float*)&_location.x, -100.0f, 200.0f);
	ImGui::SliderFloat("Location.y", (float*)&_location.y, -100.0f, 200.0f);
	ImGui::SliderInt("CurState", (int*)&_curstate, 0, 6);
	ImGui::Text("_isLeft : %d", _isLeft);
	ImGui::Text("_isTurn : %d", _isTurn);
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
	if (_isJump == false && _isAttack == false && _isTurn == false)
	{
		TotalUpdate(IDLE);
		SetState(IDLE);
	}

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

	if (_chargeTime > 1.3f)
	{
		TotalUpdate(ATTACK);
		SetAndResetState(ATTACK);
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
		_isAttack = false;
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
	TotalUpdate(ATTACKREADY);
	SetState(ATTACKREADY);
}

void Boss::JumpAttackPattern()
{
}

void Boss::AfterGroggyPattern()
{
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
