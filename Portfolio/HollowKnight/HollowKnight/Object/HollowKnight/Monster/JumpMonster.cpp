#include "framework.h"
#include "JumpMonster.h"

JumpMonster::JumpMonster()
{
	_speed = 100.0f;
	_col = make_shared<RectCollider>(Vector2(95, 180));
	_landPoint = make_shared<CircleCollider>(20);
	_transform->SetParent(_col->GetTransform());
	CreateAction(L"Resource/Monster/Jump/JM_Idle.png", "Resource/Monster/Jump/JM_Idle.xml", "Idle", Vector2(95, 207), Action::Type::LOOP);
	_actions[0]->SetSpeed(0.3);
	CreateAction(L"Resource/Monster/Jump/JM_Walk.png", "Resource/Monster/Jump/JM_Walk.xml", "Idle", Vector2(134, 194), Action::Type::LOOP);
	_actions[1]->SetSpeed(0.2);
	CreateAction(L"Resource/Monster/Jump/JM_Turn.png", "Resource/Monster/Jump/JM_Turn.xml", "Idle", Vector2(81, 207), Action::Type::END, std::bind(&JumpMonster::TurnEvent, this));
	_actions[2]->SetSpeed(0.2);
	CreateAction(L"Resource/Monster/Jump/JM_JumpReady.png", "Resource/Monster/Jump/JM_JumpReady.xml", "Idle", Vector2(176, 200), Action::Type::END, std::bind(&JumpMonster::JumpEvent, this));
	CreateAction(L"Resource/Monster/Jump/JM_Jump.png", "Resource/Monster/Jump/JM_Jump.xml", "Idle", Vector2(176, 200), Action::Type::END);
	_actions[4]->SetSpeed(0.25);
	CreateAction(L"Resource/Monster/Jump/JM_Down.png", "Resource/Monster/Jump/JM_Down.xml", "Idle", Vector2(178, 203), Action::Type::END, std::bind(&JumpMonster::JumpEvent, this));
	_actions[5]->SetSpeed(0.15);
	CreateAction(L"Resource/Monster/Jump/JM_Land.png", "Resource/Monster/Jump/JM_Land.xml", "Idle", Vector2(131, 166), Action::Type::END, std::bind(&JumpMonster::LandEvent, this));
	_actions[6]->SetSpeed(0.2);
}

JumpMonster::~JumpMonster()
{
}

void JumpMonster::Update()
{
	if (_targetPlayer.expired() == true)
		return;
	if (_isAlive == false)
		return;

	Monster::Update();

	Gravity(_col);
	_col->Update();
	_landPoint->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	_attackCoolTime += DELTA_TIME;
	_turnCoolTime += DELTA_TIME;

	if (_attackCoolTime > 2.0f)
		_attackCoolTime = 2.0f;

	if (_turnCoolTime > 0.5f)
		_turnCoolTime = 0.5f;

	if (_isActive == true)
		_col->SetRed();

	UnActiveIDle(); // Active가 비활성화 되어있을 때 Idle 모션으로 변경
	LandMotionChange(); // 낙하모션으로 바꿈
	Active(); // 타겟이 일정거리 안으로 오면 Active 활성
	AttackStart(); // 타겟이 일정거리 안으로 오면 공격 실시
	JumpMove(); // 점프하는 동안 움직일 수 있게 해줌
	DirFix(); // 타겟쪽으로 방향 전환 & 점프동안 방향고정
	WalkChange(); // Active활성화 됬을 때 걷는 모션으로 변경 및 타겟으로 걸어가게 하기

}

void JumpMonster::Render()
{
	if (_targetPlayer.expired() == true)
		return;

	if (_isAlive == false)
		return;

	Monster::Render();
	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();

	_col->Render();
	// _landPoint->Render();
}

void JumpMonster::PostRender()
{
	ImGui::Text("SPEED : %f", _speed);
	ImGui::Text("_isAttack : %d", _isAttack);
	ImGui::Text("_isJump : %d", _isJump);
	ImGui::Text("_isActive : %d", _isActive);
	ImGui::Text("_isLeft : %d", _isLeft);
	ImGui::Text("_isTurn : %d", _isturn);
	ImGui::Text("_dir : %f", _dir.x);

}

void JumpMonster::Attack()
{
	if (_isAttack == true || _isJump == true)
		return;
	if (_isturn == true)
		return;

	_isAttack = true;
	_actions[JUMPREADY]->Update();
	TotalUpdate(JUMPREADY);
	SetState(JUMPREADY);
	_actions[JUMPREADY]->Play();
}

void JumpMonster::SetState(State_JumpMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
}

void JumpMonster::SetAndResetState(State_JumpMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
	_actions[_oldstate]->Reset();
}

void JumpMonster::SetAndPlayState(State_JumpMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
}

void JumpMonster::TotalUpdate(State_JumpMonster type)
{
	_transform->Update();
	_actions[type]->Update();
	_sprites[type]->Update();
}

void JumpMonster::Turn()
{
	if (_isturn == true)
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
		if (_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x < 0)
		{
			_isturn = true;
			_actions[TURN]->Update();
			TotalUpdate(TURN);
			SetState(TURN);
		}
		return;
	}

	if (_isLeft == false)
	{
		if (_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x > 0)
		{
			_isturn = true;
			TotalUpdate(TURN);
			SetState(TURN);
		}
		return;
	}

}

void JumpMonster::TurnEvent()
{
	if (_isLeft == false)
		SetLeft();
	else
		SetRight();
	_actions[1]->Update();
	_isturn = false;
}

void JumpMonster::JumpEvent()
{
	if (_curstate == JUMPREADY)
	{
		_isJump = true;
		_landPoint->SetPosition(_targetPlayer.lock()->GetTransform()->GetWorldPosition());
		TotalUpdate(JUMP);
		SetAndResetState(JUMP);
		//_actions[DOWN]->Reset();
		_jumpPower = 800.0f;
	}

	if (_curstate == DOWN)
	{
		_isJump = false;
		_actions[LAND]->Update();
		TotalUpdate(LAND);
		SetAndResetState(LAND);
	}
}

void JumpMonster::LandEvent()
{
	_actions[IDLE]->Update();
	TotalUpdate(IDLE);
	SetState(IDLE);
	_attackCoolTime = 0.0f;
	_isAttack = false;
}
#pragma region Update Finction
void JumpMonster::UnActiveIDle()
{
	if (_isActive == false)
	{
		if (_isturn == true)
			return;
		if (_isAttack == true)
			return;
		_actions[IDLE]->Update();
		TotalUpdate(IDLE);
		SetState(IDLE);
		_col->SetGreen();
	}
}

void JumpMonster::LandMotionChange()
{
	if (_isJump == true && _jumpPower < 0)
	{
		if (_curstate == DOWN)
			return;

		_actions[DOWN]->Update();
		TotalUpdate(DOWN);
		SetState(DOWN);
		_actions[DOWN]->Play();
	}
}

void JumpMonster::Active()
{
	if (abs(_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _targetPlayer.lock()->GetTransform()->GetWorldPosition().y < 500.0f) || _isJump == true)
		_isActive = true;
	else
	{
		_isActive = false;
		_isJump = false;
	}
}

void JumpMonster::AttackStart()
{
	if (abs(_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x) < 250.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _targetPlayer.lock()->GetTransform()->GetWorldPosition().y < 500.0f) || _isJump == true)
	{
		if (_isAttack == true)
			return;
		if (_attackCoolTime < 1.9f)
			return;
		Attack();
	}
}

void JumpMonster::JumpMove()
{
	if (_isJump == true)
	{
		_speed = (Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_landPoint->GetTransform()->GetWorldPosition().x, 0.0f)).Length();
		if (_isLeft == true)
			_dir.x = -1;
		else
			_dir.x = 1;
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	}

}

void JumpMonster::DirFix()
{
	if (_isJump == false && _dir.Length() != 0)
	{
		_dir = Vector2(_targetPlayer.lock()->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NormalVector2();
	}
}

void JumpMonster::WalkChange()
{
	if (_isActive == true)
	{
		Turn();
		if (_isturn == true)
			return;
		if (_isAttack == true)
			return;
		_speed = 100.0f;

		_actions[WALK]->Update();
		TotalUpdate(WALK);
		SetState(WALK);
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	}
}

#pragma endregion

void JumpMonster::SetLeft()
{
	_actions[_curstate]->Update();
	static_pointer_cast<RectCollider>(_col)->SetScale(Vector2(-1, 1));
	_isLeft = true;
}

void JumpMonster::SetRight()
{
	_actions[_curstate]->Update();
	static_pointer_cast<RectCollider>(_col)->SetScale(Vector2(1, 1));
	_isLeft = false;
}
