#include "framework.h"
#include "RushMonster.h"

RushMonster::RushMonster()
{
	_speed = 100.0f;
	_hp = 5;
	_col = make_shared<RectCollider>(Vector2(95, 180));
	_transform->SetParent(_col->GetTransform());
	CreateAction(L"Resource/Monster/Rush/RushIdle.png", "Resource/Monster/Rush/RushIdle.xml", "Idle",
	Vector2(116, 195), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushWalk.png", "Resource/Monster/Rush/RushWalk.xml", "Walk",
	Vector2(136, 177), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushReady.png", "Resource/Monster/Rush/RushReady.xml", "RushReady",
	Vector2(167, 188), Action::Type::END, std::bind(&RushMonster::RushEvent, this));
	CreateAction(L"Resource/Monster/Rush/RushRush.png", "Resource/Monster/Rush/RushRush.xml", "Rush",
	Vector2(180, 115), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushEnd1.png", "Resource/Monster/Rush/RushEnd1.xml", "End1",
	Vector2(167, 188), Action::Type::END, std::bind(&RushMonster::RushEvent, this));
	CreateAction(L"Resource/Monster/Rush/RushTurn.png", "Resource/Monster/Rush/RushTurn.xml", "Turn",
	Vector2(103, 195), Action::Type::END, std::bind(&RushMonster::TurnEvent, this));
	CreateAction(L"Resource/Monster/Rush/RushTurn.png", "Resource/Monster/Rush/RushTurn.xml", "Idle",
	Vector2(103, 195), Action::Type::END, std::bind(&RushMonster::TurnEvent, this));
	CreateAction(L"Resource/Monster/Rush/RushTurn.png", "Resource/Monster/Rush/RushTurn.xml", "Idle",
	Vector2(103, 195), Action::Type::END, std::bind(&RushMonster::TurnEvent, this));


	_actions[IDLE]->SetSpeed(0.3);
	_actions[WALK]->SetSpeed(0.2);
	_actions[TURN]->SetSpeed(0.2);
}

RushMonster::~RushMonster()
{
}

void RushMonster::Update()
{
	if (_targetPlayer.expired() == true)
		return;

	if (_hp < 0)
	{
		_hp = 0;
		_isAlive = false;
	}

	if (_isAlive == false)
	{
		return;
	}

	Monster::Update();

	if (_isRush == true)
		_rushTime += DELTA_TIME;

	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
		_col->SetGreen();

	_attackCoolTime += DELTA_TIME;
	_turnCoolTime += DELTA_TIME;
	Gravity(_col);
	_col->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
		_col->SetGreen();

	if(_curstate == RUSH)
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	if (_isRush == false)
	{
		_dir = Vector2(_targetPlayer.lock()->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NormalVector2();
	}

	//RightLeft();
	WalkChange();
	Active();
	UnActiveIdle();

	if (_rushTime > 2.5f)
		RushFinish();

	if (abs(_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x) < 300.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _targetPlayer.lock()->GetTransform()->GetWorldPosition().y < 500.0f) || _isRush == true)
	{
		Attack();
	}
	Hitted(_col);
	UnbeatableToIdle();
}

void RushMonster::Render()
{
	if (_targetPlayer.expired() == true)
		return;

	Monster::Render();
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();
	_col->Render();
}

void RushMonster::PostRender()
{
	ImGui::Text("SPEED : %f", _speed);
	ImGui::Text("_isturn : %d", _isTurn);
	ImGui::Text("_jmisleft : %d", _isLeft);
}

void RushMonster::Attack()
{
	if (_isRush == true)
		return;
	if (_isTurn == true)
		return;
	if (_attackCoolTime < 3.0f)
		return;
	_isRush = true;
	_speed = 0.0f;
	TotalUpdate(RUSHREADY);
	SetAndPlayState(RUSHREADY);
}

void RushMonster::AllStop()
{
	_isRush = false;
	_isTurn = false;
}

void RushMonster::SetState(State_RushMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

}

void RushMonster::SetAndResetState(State_RushMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
	_actions[_oldstate]->Reset();
}

void RushMonster::SetAndPlayState(State_RushMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
}

void RushMonster::TotalUpdate(State_RushMonster type)
{
	_transform->Update();
	_actions[type]->Update();
	_sprites[type]->Update();
}

void RushMonster::Turn()
{
	if (_isTurn == true)
		return;
	if (_isRush == true)
		return;
	if (_turnCoolTime < 0.4f)
		return;

	_actions[TURN]->Reset();
	_actions[TURN]->Play();

	if (_isLeft == true)
	{
		if (_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x < 0)
		{
			_isTurn = true;
			TotalUpdate(TURN);
			SetState(TURN);
		}
		return;
	}

	if (_isLeft == false)
	{
		if (_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x > 0)
		{
			_isTurn = true;
			TotalUpdate(TURN);
			SetState(TURN);
		}
		return;
	}
}

void RushMonster::UnActiveIdle()
{
	if (_isActive == false)
	{
		if (_isTurn == true)
			return;
		if (_isRush == true)
			return;
		TotalUpdate(IDLE);
		SetState(IDLE);
		_col->SetGreen();
	}
}

void RushMonster::Active()
{
	if (abs(_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _targetPlayer.lock()->GetTransform()->GetWorldPosition().y < 500.0f) || _isRush == true)
		_isActive = true;
	else
	{
		_isActive = false;
		_isRush = false;
	}

	if (_isActive == true)
	{
		if (_isRush == true)
			return;
		_speed = 100.0f;
	}
}

void RushMonster::RightLeft()
{
	if (_dir.x < 0.0f)
		SetLeft();
	else
		SetRight();
}

void RushMonster::WalkChange()
{
	if (_isActive == true)
	{
		Turn();
		if (_isTurn == true)
			return;
		if (_isRush == true)
			return;
		_speed = 100.0f;

		TotalUpdate(WALK);
		SetState(WALK);
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	}
}

void RushMonster::RushEvent()
{
	if (_curstate == RUSHREADY)
	{
		if (_isLeft == true)
			_dir.x = -1.0f;
		else
			_dir.x = 1.0f;
		_speed = 300.0f;
		_transform->AddVector2(Vector2(0, -35));
		TotalUpdate(RUSH);
		SetAndResetState(RUSH);
	}

	if (_curstate == RUSHEND)
	{
		TotalUpdate(IDLE);
		SetAndResetState(IDLE);
		_isRush = false;
	}
}

void RushMonster::RushFinish()
{
	if (_curstate == RUSH)
	{
		_transform->AddVector2(Vector2(0, 35));
		TotalUpdate(RUSHEND);
		SetAndResetState(RUSHEND);
		_speed = 0.0f;
		_rushTime = 0.0f;
		_attackCoolTime = 0.0f;

	}
}

void RushMonster::TurnEvent()
{
	if (_isLeft == false)
		SetLeft();
	else
		SetRight();
	_isTurn = false;
}

void RushMonster::SetLeft()
{
	_actions[_curstate]->Update();
	static_pointer_cast<RectCollider>(_col)->SetScale(Vector2(-1, 1));
	_isLeft = true;
}

void RushMonster::SetRight()
{
	_actions[_curstate]->Update();
	static_pointer_cast<RectCollider>(_col)->SetScale(Vector2(1, 1));
	_isLeft = false;
}
