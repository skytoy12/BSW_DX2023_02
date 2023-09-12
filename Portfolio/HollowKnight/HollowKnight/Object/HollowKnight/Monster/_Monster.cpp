#include "framework.h"
#include "_Monster.h"

using namespace tinyxml2;

Monster::Monster()
{
	_transform = make_shared<Transform>();
	_monsterBuffer = make_shared<MonsterBuffer>();
	_monsterBuffer->_data.state = 1;
	EffectManager::GetInstance()->AddEffect("Hitted", L"Resource/Effect/HitEffect.png", Vector2(1, 3), Vector2(699, 140));
	EFFECT_S("Hitted", Vector2(1.5f, 1.5f));
}

void Monster::Update()
{
	_transform->Update();
	_monsterBuffer->Update();


	EFFECT_R("Hitted", -30);
}

void Monster::Render()
{
	_transform->SetBuffer(0);
	_monsterBuffer->SetPSBuffer(1);
}



void Monster::targetHit(shared_ptr<Collider> col)
{
	if (_targetPlayer.lock()->_isUnbeatable == true)
		return;

	if (col->IsCollision(_targetPlayer.lock()->GetCollider()))
	{
		if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) < 0) // 몬스터가 플레이어보다 오른쪽에 있을 때
			_targetPlayer.lock()->SetKBdir(Vector2(-1, 0));
		else if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) > 0) // 몬스터가 플레이어보다 왼쪽에 있을 때
			_targetPlayer.lock()->SetKBdir(Vector2(1, 0));
		_targetPlayer.lock()->Hitted();
	}
}

void Monster::ExtraHit(shared_ptr<Collider> hitcol, shared_ptr<Collider> dircol)
{
	if (_targetPlayer.lock()->_isUnbeatable == true)
		return;

	if (hitcol->IsCollision(_targetPlayer.lock()->GetCollider()))
	{
		if ((_targetPlayer.lock()->WORLD.x - dircol->WORLD.x) < 0) // 몬스터가 플레이어보다 오른쪽에 있을 때
			_targetPlayer.lock()->SetKBdir(Vector2(-1, 0));
		else if ((_targetPlayer.lock()->WORLD.x - dircol->WORLD.x) > 0) // 몬스터가 플레이어보다 왼쪽에 있을 때
			_targetPlayer.lock()->SetKBdir(Vector2(1, 0));
		_targetPlayer.lock()->Hitted();
	}
}

void Monster::Hitted(shared_ptr<Collider> col)
{
	if (col->IsCollision(_targetPlayer.lock()->GetWeaponcol()))
		_targetPlayer.lock()->GetWeaponcol()->SetRed();

	if (_targetPlayer.expired() == true)
		return;
	if (_isUnbeatable == true)
		return;
	if (_monsterType == BOSS)
	{
		if (_targetPlayer.lock()->_isWeaponActiveB == false)
			return;
	}

	if (_monsterType == FLY)
	{
		if (_targetPlayer.lock()->_isWeaponActiveF == false)
			return;
	}

	if (_monsterType == JUMP)
	{
		if (_targetPlayer.lock()->_isWeaponActiveJ == false)
			return;
	}

	if (_monsterType == RUSH)
	{
		if (_targetPlayer.lock()->_isWeaponActiveR == false)
			return;
	}

	if (col->IsCollision(_targetPlayer.lock()->GetWeaponcol()))
	{
		EFFECT_LPLAY("Hitted", col->GetTransform()->GetWorldPosition());
		_monsterBuffer->_data.R = 0.5f;
		_monsterBuffer->_data.G = 0.5f;
		_monsterBuffer->_data.B = 0.5f;
		_isUnbeatable = true;
		_targetPlayer.lock()->SetWeaponActive(false);
		_targetPlayer.lock()->MPRecovery();
		WeaponActive();
		_jumpPower = 300.0f;
		if (_monsterType == RUSH)
			_speed = 100.0f;

		if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) < 0) // 몬스터가 플레이어보다 오른쪽에 있을 때
			_KBdir = Vector2(1, 0);
		else if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) > 0) // 몬스터가 플레이어보다 왼쪽에 있을 때
			_KBdir = Vector2(-1, 0);
		_KBspeed = 600;
		if (_hp == 1 && _monsterType != FLY)
			_KBspeed = 16000;
		_hp -= 1;
	}
}

void Monster::BulletHitted(shared_ptr<Collider> col)
{

	if (_targetPlayer.expired() == true)
		return;
	if (_isUnbeatable == true)
		return;
	if (_targetPlayer.lock()->GetBulletActive() == false)
		return;
	
	if (col->IsCollision(_targetPlayer.lock()->GetBulletcol()))
	{
		EFFECT_LPLAY("Hitted", col->GetTransform()->GetWorldPosition());
		_monsterBuffer->_data.R = 0.5f;
		_monsterBuffer->_data.G = 0.5f;
		_monsterBuffer->_data.B = 0.5f;
		_isUnbeatable = true;
		_targetPlayer.lock()->SetBulletActive(false);
		_jumpPower = 300.0f;
		if (_monsterType == RUSH)
			_speed = 100.0f;

		if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) < 0) // 몬스터가 플레이어보다 오른쪽에 있을 때
			_KBdir = Vector2(1, 0);
		else if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) > 0) // 몬스터가 플레이어보다 왼쪽에 있을 때
			_KBdir = Vector2(-1, 0);
		_KBspeed = 600;

		_hp -= 5;
		if (_hp <= 0)
			_hp = 0;

		if (_hp == 0 && _monsterType != FLY)
			_KBspeed = 16000;
	}
}

void Monster::HitKnockBack(shared_ptr<Collider> col)
{
	if(_isUnbeatable == true)
		col->GetTransform()->AddVector2(_KBdir * _KBspeed * DELTA_TIME);
}

void Monster::WeaponActive()
{
	if (_monsterType == BOSS)
		_targetPlayer.lock()->_isWeaponActiveB = false;

	if (_monsterType == FLY)
		_targetPlayer.lock()->_isWeaponActiveF = false;

	if (_monsterType == JUMP)
		_targetPlayer.lock()->_isWeaponActiveJ = false;

	if (_monsterType == RUSH)
		_targetPlayer.lock()->_isWeaponActiveR = false;
}

void Monster::UnbeatableToIdle()
{
	if (_isUnbeatable == true)
		_unbeatableTime += DELTA_TIME;

	if (_unbeatableTime > 0.1f && _unbeatableTime < 0.2f && _monsterType != BOSS)
		_jumpPower = -400.0f;

	if (_unbeatableTime < 0.2f)
		return;
	_isUnbeatable = false;
	_unbeatableTime = 0.0f;
	SetRGB(0.0f, 0.0f, 0.0f);
}

void Monster::SetRGB(float R, float G, float B)
{
	_monsterBuffer->_data.R = R;
	_monsterBuffer->_data.G = G;
	_monsterBuffer->_data.B = B;
}

void Monster::EffectSetting()
{
	//if(_targetPlayer.lock()->GetTransform()->GetWorldPosition().x - )
}

void Monster::Gravity(shared_ptr<Collider> col)
{
	_jumpPower -= 15;

	if (_jumpPower < -600.0f)
		_jumpPower = -600.0f;


	col->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
}


void Monster::HighGravity(shared_ptr<Collider> col)
{
	_jumpPower -= 15;

	if (_jumpPower < -2000.0f)
		_jumpPower = -2000.0f;


	col->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
}

void Monster::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmmlPath.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;


	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);


	sprite->SetPS(ADD_PS(L"Shader/MonsterPS.hlsl"));
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}
