#include "Framework.h"
#include "ShotGun.h"

ShotGun::ShotGun(string file)
	:Gun(file)
{
	for (int i = 0; i < 20; i++)
	{
		Bullet* bullet = new Bullet();
		bullet->SetTarget(this);

		bullets.push_back(bullet);
	}
}

ShotGun::~ShotGun()
{
	for (Bullet* bullet : bullets)
		delete bullet;
	bullets.clear();
}

void ShotGun::Update()
{
	Gun::Update();
	for (Bullet* bullet : bullets)
		bullet->Update();



}

void ShotGun::Render()
{
	Gun::Render();

	if (isAttack == false)
		return;

}

void ShotGun::PostRender()
{
	Debug();
}

void ShotGun::Debug()
{
}

void ShotGun::Fire()
{
	for (Bullet* bullet : bullets)
	{
		Vector3 pos = { 0, 0, 0 };
		Vector3 dir = pos;
		dir.y = 5.0f;
		dir.x = dir.x + Random(0.1f, 0.3f);
		dir.y = dir.y + Random(0.1f, 0.3f);
		dir.z = dir.z + Random(0.1f, 0.3f);

		dir = dir - bullet->GetOrigin();
		dir.Normalize();
		bullet->SetDestination(dir);
	}
}
