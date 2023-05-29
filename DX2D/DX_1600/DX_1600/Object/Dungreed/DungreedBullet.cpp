#include "framework.h"
#include "DungreedBullet.h"
DungreedBullet::DungreedBullet()
{
	_quad = make_shared<Quad>(L"Resource/Dungreed/Bullet.png");
	_quad->GetTransform()->SetScale({ 0.05f, 0.05f });
}

DungreedBullet::~DungreedBullet()
{
}

void DungreedBullet::Update()
{
	if (!_isActive)
		return;
	_quad->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	_quad->Update();
}

void DungreedBullet::Render()
{
	if (!_isActive)
		return;
	_quad->Render();
}

void DungreedBullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_quad->GetTransform()->SetPosition(startPos);
	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_quad->GetTransform()->SetAngle(angle);
}
