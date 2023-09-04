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



void Monster::Hitted(shared_ptr<Collider> col)
{
	if (col->IsCollision(_targetPlayer.lock()->GetWeaponcol()))
		_targetPlayer.lock()->GetWeaponcol()->SetRed();

	if (_targetPlayer.expired() == true)
		return;
	if (_isUnbeatable == true)
		return;
	if (_targetPlayer.lock()->GetWeaponActive() == false)
		return;

	if (col->IsCollision(_targetPlayer.lock()->GetWeaponcol()))
	{
		EFFECT_LPLAY("Hitted", col->GetTransform()->GetWorldPosition());
		_monsterBuffer->_data.R = 0.5f;
		_monsterBuffer->_data.G = 0.5f;
		_monsterBuffer->_data.B = 0.5f;
		_isUnbeatable = true;
		_targetPlayer.lock()->SetWeaponActive(false);
		_hp -= 1;
		_jumpPower = 300.0f;
		if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) < 0) // 몬스터가 플레이어보다 오른쪽에 있을 때
			_dir = Vector2(1, 0);
		else if ((_targetPlayer.lock()->WORLD.x - col->WORLD.x) > 0) // 몬스터가 플레이어보다 왼쪽에 있을 때
			_dir = Vector2(-1, 0);
	}
}

void Monster::UnbeatableToIdle()
{
	if (_isUnbeatable == true)
		_unbeatableTime += DELTA_TIME;

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
