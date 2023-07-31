#include "framework.h"
#include "RushMonster.h"

RushMonster::RushMonster()
{
	_speed = 100.0f;
	_col = make_shared<RectCollider>(Vector2(95, 180));
	_transform->SetParent(_col->GetTransform());
	CreateAction(L"Resource/Monster/Rush/RushIdle.png", "Resource/Monster/Rush/RushIdle.xml", "Idle", Vector2(116, 195), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushWalk.png", "Resource/Monster/Rush/RushWalk.xml", "Idle", Vector2(136, 177), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushReady.png", "Resource/Monster/Rush/RushReady.xml", "Idle", Vector2(167, 188), Action::Type::END, std::bind(&RushMonster::RushEvent, this));
	CreateAction(L"Resource/Monster/Rush/RushRush.png", "Resource/Monster/Rush/RushRush.xml", "Idle", Vector2(180, 115), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushEnd.png", "Resource/Monster/Rush/RushEnd.xml", "Idle", Vector2(131, 161), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Rush/RushTurn.png", "Resource/Monster/Rush/RushTurn.xml", "Idle", Vector2(103, 195), Action::Type::LOOP);
}

RushMonster::~RushMonster()
{
}

void RushMonster::Update()
{
	if (_target.expired() == true)
		return;

	if (_isAlive == false)
		return;

	if (_isRush == true)
		_rushTime += DELTA_TIME;

	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
		_col->SetGreen();

	_attackCoolTime += DELTA_TIME;
	Gravity(_col);
	_col->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
		_col->SetGreen();


	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f) || _isRush == true)
		_isActive = true;
	else
	{
		_isActive = false;
		_isRush = false;
	}

	if (_isRush == false)
	{
		_dir = Vector2(_target.lock()->GetWorldPosition().x, 0.0f) - Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NomalVector2();
	}

	RightLeft();
	WalkChange();
	Active();

	if (_rushTime > 2.5f)
		RushFinish();

	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 300.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f) || _isRush == true)
	{
		Attack();
	}
}

void RushMonster::Render()
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

void RushMonster::PostRender()
{
	ImGui::Text("SPEED : %f", _speed);
}

void RushMonster::Attack()
{
	if (_isRush == true)
		return;
	if (_attackCoolTime < 3.0f)
		return;
	_isRush = true;
	_speed = 0.0f;
	SetAndPlayState(RUSHREADY);
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

void RushMonster::Active()
{
	if (_isActive == true)
	{
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
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

		if (_isRush == true)
			return;
		_speed = 100.0f;

		_actions[WALK]->Update();
		SetState(WALK);
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	}
}

void RushMonster::RushEvent()
{
	if (_curstate == RUSHREADY)
	{
		_dir = Vector2(_target.lock()->GetWorldPosition().x, 0.0f) - Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NomalVector2();
		_speed = 300.0f;
		SetAndResetState(RUSH);
	}
}

void RushMonster::RushFinish()
{
	if (_curstate == RUSH)
	{
		SetAndResetState(IDLE);
		_speed = 0.0f;
		_isRush = false;
		_rushTime = 0.0f;
		_attackCoolTime = 0.0f;
	}
}

void RushMonster::SetLeft()
{
	_actions[_curstate]->Update();
	_col->SetScale(Vector2(-1, 1));
	_isLeft = true;
}

void RushMonster::SetRight()
{
	_actions[_curstate]->Update();
	_col->SetScale(Vector2(1, 1));
	_isLeft = true;
}
