#include "framework.h"
#include "JumpMonster.h"

JumpMonster::JumpMonster()
{
	_col = make_shared<RectCollider>(Vector2(95, 207));
	_transform->SetParent(_col->GetTransform());
	CreateAction(L"Resource/Monster/Jump/JM_Idle.png", "Resource/Monster/Jump/JM_Idle.xml", "Idle", Vector2(95, 207), Action::Type::LOOP);
	_actions[0]->SetSpeed(0.2);
	CreateAction(L"Resource/Monster/Jump/JM_Walk.png", "Resource/Monster/Jump/JM_Walk.xml", "Idle", Vector2(95, 207), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Jump/JM_Turn.png", "Resource/Monster/Jump/JM_Turn.xml", "Idle", Vector2(95, 207), Action::Type::END);
	CreateAction(L"Resource/Monster/Jump/JM_JumpReady.png", "Resource/Monster/Jump/JM_JumpReady.xml", "Idle", Vector2(95, 207), Action::Type::END);
	CreateAction(L"Resource/Monster/Jump/JM_Jump.png", "Resource/Monster/Jump/JM_Jump.xml", "Idle", Vector2(95, 207), Action::Type::END);
	CreateAction(L"Resource/Monster/Jump/JM_Down.png", "Resource/Monster/Jump/JM_Down.xml", "Idle", Vector2(95, 207), Action::Type::END);
	CreateAction(L"Resource/Monster/Jump/JM_Land.png", "Resource/Monster/Jump/JM_Land.xml", "Idle", Vector2(95, 207), Action::Type::END);

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
	if(_isActive == false)
		_col->SetGreen();

	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f)) // || _isJump == true)
		_isActive = true;
	else
	{
		_isActive = false;
		_isJump = false;
	}

	if (_isJump == false)
	{
		_dir = Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_target.lock()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NormalVector2() * -1;
	}

	_speed = 150.0f;
	if(_isActive == true)
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	if (_isActive == true)
		Attack();

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
}

void JumpMonster::Attack()
{
	if (_isJump == true)
		return;

	_isJump = true;
	_jumpPower = 800.0f;
}

void JumpMonster::SetState(State_JumpMonster type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
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
