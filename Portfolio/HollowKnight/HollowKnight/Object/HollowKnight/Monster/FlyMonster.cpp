#include "framework.h"
#include "FlyMonster.h"

FlyMonster::FlyMonster(Vector2 pos)
{
	_monsterType = Monster::MonsterType::FLY;

	_hp = 3;

	_col = make_shared<CircleCollider>(40);
	_rangePoint = make_shared<CircleCollider>(20);


	CreateAction(L"Resource/Monster/Fly/FLYIDLE.png", "Resource/Monster/Fly/FLYIDLE.xml", "Idle",
	Vector2(95, 115), Action::Type::LOOP);

	CreateAction(L"Resource/Monster/Fly/FLYDEATH2.png", "Resource/Monster/Fly/FLYDEATH2.xml", "Idle",
	Vector2(110, 97), Action::Type::END, std::bind(&FlyMonster::DeathEvent, this));

	CreateAction(L"Resource/Monster/Fly/FLYDEATH1.png", "Resource/Monster/Fly/FLYDEATH1.xml", "Idle",
	Vector2(90, 87), Action::Type::END, std::bind(&FlyMonster::DeathEvent, this));

	_col->SetObjectType(Collider::ObjectType::MONSTER);
	_transform->SetParent(_col->GetTransform());
	_col->SetPosition(pos);
	_originPos = pos;
	_rangePoint->SetPosition(_originPos);
	_actions[IDLE]->SetSpeed(0.20f);
}

FlyMonster::~FlyMonster()
{
}

void FlyMonster::Update()
{
	if (_targetPlayer.expired() == true)
		return;

	if (_isDeath == true)
	{
		if (_deathTime > 1.0f)
			return;
		_deathTime += DELTA_TIME;
		Gravity(_col);
		_col->Update();
		_transform->Update();
		return;
	}


	if (_hp <= 0)
	{
		_hp = 0;
		_isAlive = false;
	}

	if (_isAlive == false)
	{
		DeathStart();
	}


	Monster::Update();

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


	CreateRangePoint();
	RightLeft();
	UnActive();
	Active();


	targetHit(_col);

	if (_isAlive == true)
	{
		Hitted(_col);
		HitKnockBack(_col);
		BulletHitted(_col);
	}
	UnbeatableToIdle();
}

void FlyMonster::Render()
{
	if (_targetPlayer.expired() == true)
		return;
	if (_isDeath == true)
		return;

	Monster::Render();
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();

	_col->Render();
	_rangePoint->Render();
}

void FlyMonster::PostRender()
{
	ImGui::Text("_dir.x : %f", _dir.x);
	ImGui::Text("_dir.y : %f", _dir.y);
	ImGui::Text("FLYJP : %f", _jumpPower);
}

void FlyMonster::Attack()
{
	if (_isAlive == false)
		return;

	CreateRandomPos();

	_dir = _randomPos - _col->GetTransform()->GetWorldPosition();
	_dir = _dir.NormalVector2();
	_speed = 200.0f;

	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
}

#pragma region Update Function

void FlyMonster::SetPosition(Vector2 pos)
{
	_col->SetPosition(pos);
	_originPos = pos;
}

void FlyMonster::DeathStart()
{
	if (_hp > 0)
		return;
	if (_curstate == AIRDEATH || _curstate == LANDDEATH)
		return;
	_jumpPower = 0.0f;
	_curstate = AIRDEATH;
}

void FlyMonster::DeathEvent()
{
	if (_curstate == AIRDEATH)
	{
		SetRGB(-0.5, -0.5, -0.5);
		_curstate = LANDDEATH;
		_transform->SetPosition(Vector2(0, 40));
		return;
	}

	if (_curstate == LANDDEATH)
		_isDeath = true;
}

void FlyMonster::RightLeft()
{
	if (_isAlive == false)
		return;

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
	if (_isAlive == false)
		return;

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
	if (_isAlive == false)
		return;

	if (abs(_col->GetTransform()->GetWorldPosition().x - _targetPlayer.lock()->GetTransform()->GetWorldPosition().x) < 500.0f &&
		abs(_col->GetTransform()->GetWorldPosition().y - _targetPlayer.lock()->GetTransform()->GetWorldPosition().y) < 300.0f)
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

	RandPos.x = _targetPlayer.lock()->GetTransform()->GetWorldPosition().x + MyMath::RandomFloat(-100, 100);
	RandPos.y = _targetPlayer.lock()->GetTransform()->GetWorldPosition().y + MyMath::RandomFloat(0, 70);
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
	
	static_pointer_cast<CircleCollider>(_col)->reverseScale();
	_isLeft = true;
	_turnCoolTime = 0.0f;
}

void FlyMonster::SetRight()
{
	if (_turnCoolTime < 0.2f)
		return;
	static_pointer_cast<CircleCollider>(_col)->OriginScale();
	_isLeft = false;
	_turnCoolTime = 0.0f;
}
