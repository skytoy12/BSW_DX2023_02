#include "framework.h"
#include "Cup_Boss_2phase.h"
#include "Cup_Bullet.h"
using namespace tinyxml2;

Cup_Boss_2phase::Cup_Boss_2phase()
{
	_collider = make_shared<RectCollider>(Vector2(Vector2(300, 700)));
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

	_transform->SetPosition(Vector2(20, 30));
	_intBuffer = make_shared<IntBuffer>();

	_intBuffer->_data.aInt = 3;
	_intBuffer->_data.bInt = 300;

	CreateAction(L"Resource/CupHead/Boss2/Clown_Page_Last_Spawn_Penguin_Start.png", "Resource/CupHead/Boss2/Clown_Page_Last_Spawn_Penguin_Start.xml", "START", Vector2(500, 800), Action::Type::END, std::bind(&Cup_Boss_2phase::EndEvent, this));
	CreateAction(L"Resource/CupHead/Boss2/Clown_Page_Last_Spawn_Penguin_Loop.png", "Resource/CupHead/Boss2/Clown_Page_Last_Spawn_Penguin_Loop.xml", "START", Vector2(500, 800), Action::Type::LOOP);

	EffectManager::GetInstance()->AddEffect("BossHit", L"Resource/CupHead/GreenExplosion.png", Vector2(4, 4), Vector2(100, 100));
}

Cup_Boss_2phase::~Cup_Boss_2phase()
{
}

void Cup_Boss_2phase::Update()
{
	if (_isAlive == false)
		return;

	Move(Vector2(0, 100));

	_collider->Update();
	_intBuffer->Update();
	_actions[_state]->Update();

	_sprites[_state]->Update();

	_transform->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Boss_2phase::Render()
{
	if (_isAlive == false)
		return;
	_transform->SetBuffer(0);
	_intBuffer->SetPSBuffer(1);


	_sprites[_state]->Render();

	_collider->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Boss_2phase::PostRender()
{
	if (_isAlive == false)
		return;
}



void Cup_Boss_2phase::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Boss_2phase::Fire(Vector2 targetPos)
{

	_coolTime += DELTA_TIME;
	if (_coolTime > _atkSpeed)
	{
		_coolTime = 0.0f;
	}
	else
		return;

	Vector2 dir = targetPos - _collider->GetPos();
	dir.Nomallize();

	auto bulletiter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Cup_Bullet> obj)->bool {return !obj->_isActive; });

	if (bulletiter == _bullets.end())
		return;

	(*bulletiter)->SetAngle(dir.Angle());
	(*bulletiter)->Shoot(dir, _collider->GetPos());
}

void Cup_Boss_2phase::EndEvent()
{
	if (_state == phase_State::START)
	{
		_state = phase_State::LOOP;
		_actions[_state]->Play();
		_actions[START]->Reset();
		return;
	}
}

bool Cup_Boss_2phase::isCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;


		if (col->IsCollision(bullet->GetCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("BossHit", bullet->GetCollider()->GetPos());
			return true;
		}
	}
	return false;
}

void Cup_Boss_2phase::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Boss_2phase::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
