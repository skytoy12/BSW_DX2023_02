#include "framework.h"
#include "JumpMonster.h"

JumpMonster::JumpMonster()
{
	_speed = 100.0f;
	_col = make_shared<RectCollider>(Vector2(95, 180));
	_transform->SetParent(_col->GetTransform());
	CreateAction(L"Resource/Monster/Jump/JM_Idle.png", "Resource/Monster/Jump/JM_Idle.xml", "Idle", Vector2(95, 207), Action::Type::LOOP);
	_actions[0]->SetSpeed(0.2);
	CreateAction(L"Resource/Monster/Jump/JM_Walk.png", "Resource/Monster/Jump/JM_Walk.xml", "Idle", Vector2(134, 194), Action::Type::LOOP);
	_actions[1]->SetSpeed(0.2);
	CreateAction(L"Resource/Monster/Jump/JM_Turn.png", "Resource/Monster/Jump/JM_Turn.xml", "Idle", Vector2(81, 207), Action::Type::END, std::bind(&JumpMonster::TurnEvent, this));
	_actions[2]->SetSpeed(0.25);
	CreateAction(L"Resource/Monster/Jump/JM_JumpReady.png", "Resource/Monster/Jump/JM_JumpReady.xml", "Idle", Vector2(176, 200), Action::Type::END, std::bind(&JumpMonster::JumpEvent, this));
	CreateAction(L"Resource/Monster/Jump/JM_Jump.png", "Resource/Monster/Jump/JM_Jump.xml", "Idle", Vector2(176, 200), Action::Type::END);
	CreateAction(L"Resource/Monster/Jump/JM_Down.png", "Resource/Monster/Jump/JM_Down.xml", "Idle", Vector2(178, 203), Action::Type::END);
	CreateAction(L"Resource/Monster/Jump/JM_Land.png", "Resource/Monster/Jump/JM_Land.xml", "Idle", Vector2(131, 166), Action::Type::END);

}

JumpMonster::~JumpMonster()
{
}

void JumpMonster::Update()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	Gravity(_col);
	_col->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
	{
		if (_isturn == true)
			return;
		if (_isAttack == true)
			return;
		SetState(IDLE);
		_col->SetGreen();
	}


	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f)) // || _isJump == true)
		_isActive = true;
	else
	{
		_isActive = false;
		_isJump = false;
	}

	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 250.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f)) // || _isJump == true)
	{
		if (_isAttack == true)
			return;
		Attack();
	}

	if(_isJump == true)
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	if (_isJump == false)
	{
		_dir = Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_target.lock()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NormalVector2() * -1;
	}

	if (_isActive == true)
	{
		Turn();
		if (_isturn == true)
			return;
		if (_isAttack == true)
			return;
		_speed = 100.0f;
		SetState(WALK);
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	}
}

void JumpMonster::Render()
{
	if (_target.expired() == true)
		return;

	if (_isAlive == false)
		return;

	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();

	_col->Render();
}

void JumpMonster::PostRender()
{
	ImGui::Text("SPEED : %d", _speed);
}

void JumpMonster::Attack()
{
	if (_isAttack == true || _isJump == true)
		return;

	_isAttack = true;
	SetState(JUMPREADY);
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

void JumpMonster::Turn()
{
	if (_isturn == true)
		return;
	if (_isAttack == true)
		return;


	_actions[2]->Reset();
	_actions[2]->Play();

	if (_isLeft == true)
	{
		if (_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x < 0)
		{
			_isturn = true;
			SetState(TURN);
		}
		return;
	}

	if (_isLeft == false)
	{
		if (_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x > 0)
		{
			_isturn = true;
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
		SetAndResetState(JUMP);
		_speed = 100.0f;
		_jumpPower = 800.0f;
	}

}

void JumpMonster::SetLeft()
{
	_col->SetScale(Vector2(-1, 1));
	_isLeft = true;
}

void JumpMonster::SetRight()
{
	_col->SetScale(Vector2(1, 1));
	_isLeft = false;
}
