#include "framework.h"
#include "RushMonster.h"

RushMonster::RushMonster()
{
	_col = make_shared<RectCollider>(Vector2(50,50));
	_transform->SetParent(_col->GetTransform());
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

	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
		_col->SetGreen();

	Gravity(_col);
	_col->Update();


	if (_isActive == true)
		_col->SetRed();
	if (_isActive == false)
		_col->SetGreen();


	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f)) // || _isJump == true)
		_isActive = true;
	else
	{
		_isActive = false;
		_isRush = false;
	}

	if (_isRush == false)
	{
		_dir = Vector2(_col->GetTransform()->GetWorldPosition().x, 0.0f) - Vector2(_target.lock()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NomalVector2() * -1;
	}

	if (_isActive == true)
		_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	if (_isActive == true)
		Attack();
}

void RushMonster::Render()
{
	if (_target.expired() == true)
		return;

	if (_isAlive == false)
		return;

	_col->Render();
}

void RushMonster::PostRender()
{
}

void RushMonster::Attack()
{
	_speed = 300.0f;
}
