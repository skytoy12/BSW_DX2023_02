#include "Framework.h"
#include "Rifle.h"

Rifle::Rifle(string file)
	:Gun(file)
{
	Transform::SetLabel("Rifle");
	for (int i = 0; i < bulletNum + 1; i++)
	{
		Bullet* bullet = new Bullet();
		bullets.push_back(bullet);
		bullet->SetRange(20.0f);
	}
}

Rifle::~Rifle()
{
	for (Bullet* bullet : bullets)
		delete bullet;
	bullets.clear();
}

void Rifle::Update()
{
	Gun::Update();
	for (Bullet* bullet : bullets)
		bullet->Update();


	for (Bullet* bullet : bullets)
		bullet->SetOrigin(origin);

	attackTime += Time::Delta();
	if (attackTime > 0.3f)
	{
		isAttack = false;
		for (Bullet* bullet : bullets)
			bullet->SetIsActive(false);
	}
}

void Rifle::Render()
{
	Gun::Render();
	if (isAttack == false)
		return;

	for (Bullet* bullet : bullets)
		bullet->Render();
}

void Rifle::PostRender()
{
	Debug();
}

void Rifle::Debug()
{
	Transform::Debug();
	ImGui::Text("Rifle isAttack : %d", isAttack);
}

void Rifle::Fire()
{
	dir.x = dir.x + Random(-0.01f, 0.01f);
	dir.y = dir.y + Random(-0.01f, 0.01f);
	dir.z = dir.z + Random(-0.01f, 0.01f);

	dir.Normalize();
	bullets[curBulletNum]->SetDestination(dir);
	Vector3 destination = bullets[curBulletNum]->GetOrigin() + (dir * bullets[curBulletNum]->GetRange());
	bullets[curBulletNum]->SetDestination(destination);
}

void Rifle::SetBulletActive(bool value)
{
	bullets[curBulletNum]->SetIsActive(value);
}

void Rifle::BulletNumPlus()
{
	curBulletNum += 1;

	if (curBulletNum > bulletNum)
		curBulletNum = 0;
}
