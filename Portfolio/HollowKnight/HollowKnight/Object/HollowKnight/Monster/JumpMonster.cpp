#include "framework.h"
#include "JumpMonster.h"

JumpMonster::JumpMonster()
{
	_col = make_shared<CircleCollider>(25);
	_transform->SetParent(_col->GetTransform());

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

	Gravity();
	_col->Update();

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
