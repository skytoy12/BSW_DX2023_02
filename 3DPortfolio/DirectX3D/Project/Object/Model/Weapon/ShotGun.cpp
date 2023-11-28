#include "Framework.h"
#include "ShotGun.h"

ShotGun::ShotGun(string file)
	:Gun(file)
{
	for (int i = 0; i < 20; i++)
	{
		Bullet* bullet = new Bullet();
		bullet->SetTarget(this);
		bullet->SetRange(20.0f);

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

	for (Bullet* bullet : bullets)
		bullet->SetDestination(dir);

	for (Bullet* bullet : bullets)
		bullet->SetOrigin(origin);

	attackTime += Time::Delta();
	if (attackTime > 0.5f)
		isAttack = false;
}

void ShotGun::Render()
{
	Gun::Render();

	if (isAttack == false)
		return;

	for (Bullet* bullet : bullets)
		bullet->Render();

}

void ShotGun::PostRender()
{
	Debug();
}

void ShotGun::Debug()
{
	ImGui::Text("origin : %f, %f, %f", origin.x, origin.y, origin.z);
	ImGui::Text("isAttack : %d", isAttack);
	ImGui::Text("dir : %f, %f, %f", dir.x, dir.y, dir.z);
}

void ShotGun::Fire()
{
	for (Bullet* bullet : bullets)
	{
		dir.x = dir.x + Random(-0.3f, 0.3f);
		dir.y = dir.y + Random(-0.3f, 0.3f);
		dir.z = dir.z + Random(-0.3f, 0.3f);

		dir.Normalize();
		bullet->SetDestination(dir);
	}

	for (Bullet* bullet : bullets)
		bullet->Update();

	//dir.x = dir.x + Random(0.1f, 0.3f);
	//dir.y = dir.y + Random(0.1f, 0.3f);
	//dir.z = dir.z + Random(0.1f, 0.3f);
	//dir.Normalize();

	//bullets[0]->SetDestination(dir);

	//dir.x = dir.x + Random(0.1f, 0.3f);
	//dir.y = dir.y + Random(0.1f, 0.3f);
	//dir.z = dir.z + Random(0.1f, 0.3f);
	//dir.Normalize();

	//bullets[1]->SetDestination(dir);

	//dir.x = dir.x + Random(0.1f, 0.3f);
	//dir.y = dir.y + Random(0.1f, 0.3f);
	//dir.z = dir.z + Random(0.1f, 0.3f);
	//dir.Normalize();

	//bullets[2]->SetDestination(dir);

	//dir.x = dir.x + Random(0.1f, 0.3f);
	//dir.y = dir.y + Random(0.1f, 0.3f);
	//dir.z = dir.z + Random(0.1f, 0.3f);
	//dir.Normalize();

	//bullets[3]->SetDestination(dir);

	//dir.x = dir.x + Random(0.1f, 0.3f);
	//dir.y = dir.y + Random(0.1f, 0.3f);
	//dir.z = dir.z + Random(0.1f, 0.3f);
	//dir.Normalize();

	//bullets[4]->SetDestination(dir);

	//dir.x = dir.x + Random(0.1f, 0.3f);
	//dir.y = dir.y + Random(0.1f, 0.3f);
	//dir.z = dir.z + Random(0.1f, 0.3f);
	//dir.Normalize();

	//bullets[5]->SetDestination(dir);

}
