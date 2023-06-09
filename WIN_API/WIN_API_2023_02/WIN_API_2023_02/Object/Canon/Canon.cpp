#include "framework.h"
#include "Canon.h"

Canon::Canon(Vector2 pos)
	:_isActive(true)
{
	_body = make_shared<CircleCollider>(pos, 50);
	_muzzle = make_shared<Line>(Vector2(pos), Vector2(pos.x + _muzzleLength, pos.y));

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		_bullets.push_back(bullet);
	}
	_brush = CreateSolidBrush(BLUE);
}

Canon::~Canon()
{
	DeleteObject(_brush);
}

void Canon::Update()
{
	if (_isActive == false) return;
	if (_isControlled)
	{
		Move();
		Angle();
		Fire();
	}
	CheckAttack();

	_body->Update();
	_muzzle->Update();
	for (auto& bullet : _bullets)
	{
		bullet->Update();
	}
}

void Canon::Render(HDC hdc)
{
	if (_isActive == false) return;
	_muzzle->Render(hdc);

	SelectObject(hdc, _brush);

	_body->Render(hdc);

	for (auto& bullet : _bullets)
	{
		bullet->Render(hdc);
	}
}


void Canon::Move()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->MoveCenter(Vector2(-1.0f, 0.0f));
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->MoveCenter(Vector2(1.0f, 0.0f));
	}
	_muzzle->_start = _body->GetCenter();
	_muzzle->_end = _muzzle->_start + (_muzzleDir * _muzzleLength);
}

void Canon::Angle()
{
	if (GetAsyncKeyState(VK_UP))
	{
		_muzzleAngle += 0.1f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		_muzzleAngle -= 0.1f;
	}

	_muzzleDir = Vector2(cosf(_muzzleAngle), -sinf(_muzzleAngle));
}

void Canon::Fire()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		// �����ִ� �ָ� ��
		auto iter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Bullet>& bullet)->bool
			{
				if (bullet->IsActive() == false)
					return true;
				return false;
			});
		if (iter != _bullets.end())
		{
			(*iter)->SetPos(_muzzle->_end);
			(*iter)->Shoot(_muzzleDir.NormalVector2(), 10.0f);
		}
		
	}
}

void Canon::CheckAttack()
{
	if (_target.expired())
		return;
	if (_target.lock()->_isActive == false
		|| _isActive == false
		|| _isControlled == false)
	{
		return;
	}

	for (auto& bullet : _bullets)
	{
		if (bullet->IsCollision(_target.lock()))
		{
			_target.lock()->_isActive = false;
			bullet->SetActive(false);
		}
	}
}
