#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	_collider = make_shared<CircleCollider>(50);
	_HandCollider = make_shared<CircleCollider>(20);

	CreateAction(L"Resource/CupHead/Idle.png", "Resource/CupHead/Idle.xml", "IDLE", Vector2(250, 250), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/Run.png", "Resource/CupHead/Run.xml", "RUN", Vector2(120, 120), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/Jump.png", "Resource/CupHead/Jump.xml", "JUMP", Vector2(120, 120), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/AimStraightCharge.png", "Resource/CupHead/AimStraightCharge.xml", "CHARGE", Vector2(120, 120), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/AimStraightShot.png", "Resource/CupHead/AimStraightShot.xml", "SHOT", Vector2(250, 250), Action::Type::LOOP);
	_actions[4]->SetType(Action::Type::END);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
	_HandCollider->SetParent(_collider->GetTransform());
	_transform->SetPosition(Vector2(0, 9.876));

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/CupHead/GreenExplosion.png", Vector2(4, 4), Vector2(100, 100));
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();
	Select();
	Jump();

	_collider->Update();

	_HandCollider->Update();

	_actions[_curstate]->Update();

	_sprites[_curstate]->Update();

	_transform->Update();

	for (auto bullet : _bullets)
		bullet->Update();

}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);

	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();

	_HandCollider->Render();
	_collider->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Player::PostRender()
{
	//ImGui::SliderFloat2("State", (int*)&_state, 0, 100);
	//_transform->SetPosition(_fixedPos);
}

void Cup_Player::Select()
{

	if (KEY_PRESS('A'))
	{
		if (_isJump == false)
		{
			_curstate = Cup_Player::State::RUN;
		}
		Vector2 movePos = Vector2(-500.0f, 0.0f);
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		if (_isJump == false)
		{
			_curstate = Cup_Player::State::RUN;
		}
		Vector2 movePos = Vector2(500.0f, 0.0f);
		Move(movePos);
	}

	if (KEY_UP('D'))
	{
		if (_isJump == false)
		{
			_curstate = Cup_Player::State::IDLE;
		}
	}

	if (KEY_UP('A'))
	{
		if (_isJump == false)
		{
			_curstate = Cup_Player::State::IDLE;
		}

	}

	if (KEY_PRESS(VK_LBUTTON))
	{
		if (MOUSE_POS.x < _collider->GetPos().x)
		{
			_HandCollider->SetPosition(Vector2(-60, 8));
			SetLeft();
			_curstate = Cup_Player::State::CHARGE;
		}

		if (MOUSE_POS.x > _collider->GetPos().x)
		{
			_HandCollider->SetPosition(Vector2(60, 8));
			SetRight();
			_curstate = Cup_Player::State::CHARGE;
		}
	}

	if (KEY_UP(VK_LBUTTON))
	{
		if (_isJump == false)
		{
			_curstate = Cup_Player::State::SHOT;
			Fire();
			_curstate = Cup_Player::State::IDLE;
		}
		if (_isJump == true)
		{
			_curstate = Cup_Player::State::SHOT;
			Fire();
			_curstate = Cup_Player::State::JUMP;
		}
	}

	if (_isJump == false)
	{
		if (KEY_PRESS(VK_SPACE))
		{
			_curstate = Cup_Player::State::JUMP;
			_isJump = true;
			_jumpPower = 600.0f;
		}
	}
}

void Cup_Player::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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
	_actions.push_back(action);
	_sprites.push_back(sprite);
}


void Cup_Player::Input()
{
	if (KEY_PRESS('A'))
	{
		_sprites[_curstate]->SetLeft();
	}
	
	if (KEY_PRESS('D'))
	{
		_sprites[_curstate]->SetRight();
	}
}

void Cup_Player::Jump()
{

	// �߷��ۿ�
	{
		_jumpPower -= 15;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

	
		_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}


}

void Cup_Player::AnimationControl()
{
}

void Cup_Player::Fire()
{
	Vector2 dir = MOUSE_POS - _collider->GetPos();

	auto bulletiter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Cup_Bullet> obj)->bool {return !obj->_isActive; });

	if (bulletiter == _bullets.end())
		return;
	(*bulletiter)->Shoot(Vector2(dir.x, 0.0f), _HandCollider->GetTransform()->GetWorldPosition());
}

Vector2 Cup_Player::GetBulletPos()
{
	for (auto bullet : _bullets)
	{
		return bullet->GetCollider()->GetPos();
	}
}

bool Cup_Player::isCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;


		if (col->IsCollision(bullet->GetCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("Hit", bullet->GetCollider()->GetPos());
			return true;
		}
	}
	return false;
}

void Cup_Player::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
