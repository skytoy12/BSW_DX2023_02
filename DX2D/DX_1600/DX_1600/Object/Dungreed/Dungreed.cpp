#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed()
{
	_quad = make_shared<Quad>(L"Resource/Dungreed/Player.png");

	_bowSlot = make_shared<Transform>();

	_bow = make_shared<Quad>(L"Resource/Dungreed/Bow.png");
	_bow->GetTransform()->SetParent(_bowSlot);
	_bow->GetTransform()->SetPosition({ 50, 0 });
	_bow->GetTransform()->SetAngle(-PI * 0.75f);
	for (int i = 0; i < 30; i++)
	{
		shared_ptr<DungreedBullet> bullet = make_shared<DungreedBullet>();
		bullet->_isActive = false;
		_bullets.push_back(bullet);
	}
}

Dungreed::~Dungreed()
{
}

void Dungreed::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		Fire();
	}
	SetBowAngle();


	for (auto bullet : _bullets)
	{
		if (bullet->GetPos().x > WIN_WIDTH || bullet->GetPos().y > WIN_HEIGHT || bullet->GetPos().y < 0 || bullet->GetPos().x < 0 && bullet->_isActive)
		{
			bullet->_isActive = false;
		}

	}

	_quad->Update();
	_bowSlot->Update();
	_bow->Update();
	for (auto bullet : _bullets)
		bullet->Update();
}

void Dungreed::Render()
{
	_quad->Render();
	_bow->Render();
	for (auto bullet : _bullets)
		bullet->Render();
}

void Dungreed::SetBowAngle()
{
	Vector2 playerToMouse = MOUSE_POS - GetPos();
	float angle = playerToMouse.Angle();
	_bowSlot->SetAngle(angle);
}

bool Dungreed::isCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;


		if (col->IsCollision(bullet->GetCollider()))
		{
			//bullet->_isActive = false;
			return true;
		}
	}
	return false;
}

void Dungreed::Fire()
{
	Vector2 dir = MOUSE_POS - GetPos();

	auto bulletiter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<DungreedBullet> obj)->bool {return !obj->_isActive; });

	if (bulletiter == _bullets.end())
		return;
	(*bulletiter)->Shoot(dir, _bow->GetTransform()->GetWorldPosition());
}
