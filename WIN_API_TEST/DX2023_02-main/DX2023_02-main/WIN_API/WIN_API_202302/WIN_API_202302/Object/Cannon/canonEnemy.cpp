#include "framework.h"
#include "canonEnemy.h"

canonEnemy::canonEnemy(Vector2 pos)
{
	_body = make_shared<CircleCollider>(pos, 50);
	_muzzle = make_shared<Line>(Vector2(pos), Vector2(pos.x - _muzzleLength, pos.y));
}

canonEnemy::~canonEnemy()
{
	
}

void canonEnemy::Update()
{
	Active();
	NonActive();
	_body->Update();
	_muzzle->Update();
}

void canonEnemy::Render(HDC hdc)
{
	_muzzle->Render(hdc);
	_body->Render(hdc);
}

void canonEnemy::Damaged(shared_ptr<Cannon> other)
{
	for (const auto& bullet : other->bullets())
	{
		if (bullet->IsCollision(_body))
		{
			_hp -= 10.0f;
			if (_hp <= 0.0f)
			{
				_isAlive = false;
			}
		}
	}
		
}

void canonEnemy::Active()
{
	if (GetAsyncKeyState('R'))
	{
		_isAlive = true;
	}
}

void canonEnemy::NonActive()
{
	if (GetAsyncKeyState('T'))
	{
		_isAlive = false;
	}
}
