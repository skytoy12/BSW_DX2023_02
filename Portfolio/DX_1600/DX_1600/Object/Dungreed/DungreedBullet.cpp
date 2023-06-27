#include "framework.h"
#include "DungreedBullet.h"
DungreedBullet::DungreedBullet()
{
	_collider = make_shared<CircleCollider>(1.0f);
	_quad = make_shared<Quad>(L"Resource/Dungreed/Bullet.png");
	_transform = make_shared<Transform>();

	_transform->SetParent(_collider->GetTransform());
	_transform->SetScale({ 0.05f, 0.05f });
	_transform->SetPosition({ -7.0f, 0.0f });
}

DungreedBullet::~DungreedBullet()
{
}

void DungreedBullet::Collider_Update()
{
	if (!_isActive)
		return;
	_collider->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	_collider->Update();
}

void DungreedBullet::Update()
{
	if (!_isActive)
		return;

	_transform->Update();
}

void DungreedBullet::Render()
{
	if (!_isActive)
		return;
	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}

void DungreedBullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_collider->GetTransform()->SetPosition(startPos);
	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_collider->GetTransform()->SetAngle(angle);
}
