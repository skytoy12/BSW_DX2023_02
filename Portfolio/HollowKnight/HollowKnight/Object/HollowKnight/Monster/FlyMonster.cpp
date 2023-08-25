#include "framework.h"
#include "FlyMonster.h"

FlyMonster::FlyMonster(Vector2 pos)
{
	_col = make_shared<CircleCollider>(40);
	_rangePoint = make_shared<CircleCollider>(20);
	CreateAction(L"Resource/Monster/Fly/FLYIDLE.png", "Resource/Monster/Fly/FLYIDLE.xml", "Idle", Vector2(95, 115), Action::Type::LOOP);
	_actions[IDLE]->SetSpeed(0.20f);
	CreateAction(L"Resource/Monster/Fly/FLYDEATH2.png", "Resource/Monster/Fly/FLYDEATH2.xml", "Idle", Vector2(110, 97), Action::Type::END);
	CreateAction(L"Resource/Monster/Fly/FLYDEATH1.png", "Resource/Monster/Fly/FLYDEATH1.xml", "Idle", Vector2(90, 87), Action::Type::END);
	_transform->SetParent(_col->GetTransform());
	_col->SetPosition(pos);
	_originPos = pos;
	_rangePoint->SetPosition(_originPos);
}

FlyMonster::~FlyMonster()
{
}

void FlyMonster::Update()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;
	_col->Update();
	_rangePoint->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_SRCoolTime += DELTA_TIME;
	_turnCoolTime += DELTA_TIME;

	if (_SRCoolTime > 9.0f)
		_SRCoolTime = 9.0f;

	if(abs(_dir.x) < 8.0f && abs(_dir.y) < 8.0)
		_actions[IDLE]->SetSpeed(0.20f);
	else
		_actions[IDLE]->SetSpeed(0.10f);

	if (_isActive == true)
	{
		_col->SetRed();
		Attack();
	}
	// 몬스터가 가까이있을때 떨리는 현상 _dir이 1이하일때 스피드 0으로 해서 해결해보기

	CreateRangePoint();
	RightLeft();
	UnActive();
	Active();
}

void FlyMonster::Render()
{
	if (_target.expired() == true)
		return;

	if (_isAlive == false)
		return;

	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();

	_col->Render();
	_rangePoint->Render();
}

void FlyMonster::PostRender()
{
	ImGui::Text("_dir.x : %f", _dir.x);
	ImGui::Text("_dir.y : %f", _dir.y);
	ImGui::Text("_cooltime : %f", _turnCoolTime);
}

void FlyMonster::Attack()
{
	CreateRandomPos();

	_dir = _randomPos - _col->GetTransform()->GetWorldPosition();
	_dir = _dir.NormalVector2();
	_speed = 200.0f;

	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
}

#pragma region Update Function

void FlyMonster::RightLeft()
{
	if (_dir.x < 0.0f)
		SetLeft();
	else
		SetRight();
}

void FlyMonster::CreateRangePoint()
{
	if (_isActive == true)
		return;
	if (_SRCoolTime < 8.9f)
		return;

	_searchRange = 150.0f;
	Vector2 randPos;
	float Pos;
	randPos.x = _originPos.x + MyMath::RandomFloat(-_searchRange, _searchRange);
	randPos.y = _originPos.y + MyMath::RandomFloat(-_searchRange, _searchRange);
	Pos = (_rangePoint->GetTransform()->GetWorldPosition() - randPos).Length();
	if (Pos < 150.0f)
	{
		_SRCoolTime = 50.0f;
		return;
	}
	_rangePoint->SetPosition(randPos);
	_SRCoolTime = 0.0f;
}

void FlyMonster::UnActive()
{
	if (_isActive == true)
		return;

	_col->SetGreen();
	_dir = _rangePoint->GetTransform()->GetWorldPosition() - _col->GetTransform()->GetWorldPosition();
	_speed = 1.0f;
	SpeedAverage();
	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
}

void FlyMonster::Active()
{
	if (abs(_col->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _target.lock()->GetWorldPosition().y < 500.0f))
	{
		_isActive = true;
		_actions[IDLE]->SetSpeed(0.10f);
	}
	else
	{
		_isActive = false;
	}
}

void FlyMonster::SpeedAverage()
{
	if (_dir.x > 230.0f)
		_dir.x = 230.0f;
	if (_dir.x < -230.0f)
		_dir.x = -230.0f;
	if (_dir.y > 230.0f)
		_dir.y = 230.0f;
	if (_dir.y < -230.0f)
		_dir.y = -230.0f;
}

void FlyMonster::CreateRandomPos()
{
	Vector2 RandPos;
	float Pos;

	RandPos.x = _target.lock()->GetWorldPosition().x + MyMath::RandomFloat(-100, 100);
	RandPos.y = _target.lock()->GetWorldPosition().y + MyMath::RandomFloat(0, 70);
	Pos = (_randomPos - RandPos).Length();
	if (_randomPos != Vector2(0, 0))
	{
		if (Pos < 100.0f)
			return;

		else
		{
			_SRCoolTime = 0.0f;
			_randomPos = RandPos;
		}

	}
}

#pragma endregion
void FlyMonster::SetLeft()
{
	if (_turnCoolTime < 0.2f)
		return;
	_col->reverseScale();
	_isLeft = true;
	_turnCoolTime = 0.0f;
}

void FlyMonster::SetRight()
{
	if (_turnCoolTime < 0.2f)
		return;
	_col->OriginScale();
	_isLeft = false;
	_turnCoolTime = 0.0f;
}
