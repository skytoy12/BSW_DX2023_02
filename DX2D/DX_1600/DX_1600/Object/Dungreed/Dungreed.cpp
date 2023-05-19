#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed(wstring file, Vector2 scale)
	: _scale(scale), _isWeapon(false)
{
	_quad = make_shared<Quad>(file);
	_quad->GetTransform()->SetScale(scale);

	_bow = make_shared<Transform>();
}

Dungreed::Dungreed(wstring file, Vector2 scale, int number, Vector2 bulletScale)
	: _scale(scale), _bulletScale(bulletScale), _isWeapon(true)
{
	_quad = make_shared<Quad>(file);
	_quad->GetTransform()->SetScale(scale);

	for (int i = 0; i < number; i++)
	{
		shared_ptr<DungreedBullet> bullet = make_shared<DungreedBullet>(L"Resource/Dungreed/Bullet.png", bulletScale);
		bullet->SetPosition(_quad->GetTransform()->GetPos() + Vector2(250, 10));
		_bullets.push_back(bullet);
	}

	_bow = make_shared<Transform>();
}

Dungreed::~Dungreed()
{
}

void Dungreed::Update()
{
	if (_isWeapon == true)
	{
		fire();
	}
	_bow->SetPosition(Vector2(0, 0));
	_quad->Update();
	_bow->Update();
	for (auto bullet : _bullets)
	{
		bullet->Update();
	}
}

void Dungreed::Render()
{
	_quad->Render();

	for (auto bullet : _bullets)
	{
		bullet->Render();
	}
}

void Dungreed::fire()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		auto iter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<DungreedBullet>& bullet)->bool
			{
				if (bullet->GetIsActive() == false)
					return true;
				return false;
			});
		if (iter != _bullets.end())
		{
			
			(*iter)->SetIsActive(true);
		
		}
	}
}
