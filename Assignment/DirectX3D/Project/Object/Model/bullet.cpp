#include "Framework.h"
#include "bullet.h"


Bullet::Bullet()
{
	bullet = new ColliderSphere();
}

Bullet::~Bullet()
{
	delete bullet;
}

void Bullet::Update()
{
	if (isActive == false)
		return;

	Transform::Update();

	bullet->Update();
	
	bullet->translation += bulletDir * bulletSpeed * Time::Delta();

}

void Bullet::Render()
{
	if (isActive == false)
		return;
	bullet->Render();
}

void Bullet::SetDir(Vector3 dir)
{
	bulletDir = dir;
	bulletDir.y = 0.0f;
}

void Bullet::Shoot(Vector3 pos)
{
	isActive = true;
	bullet->translation = pos;
}
