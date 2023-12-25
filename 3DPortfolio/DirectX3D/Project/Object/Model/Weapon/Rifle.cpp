#include "Framework.h"
#include "Rifle.h"

Rifle::Rifle(string file)
	:Gun(file)
{
	Transform::SetLabel("Rifle");
	for (int i = 0; i < bulletNum + 1; i++)
	{
		Bullet* bullet = new Bullet();
		bullet->SetTarget(this);
		bullet->SetRange(50.0f);

		bullets.push_back(bullet);
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

	for (Bullet* bullet : bullets)
		bullet->SetDirection(dir);

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
	ImGui::Text("Rifle Bullet1 : %d", bullets[0]->GetIsActive());
	ImGui::Text("Rifle curBulletNum : %d", curBulletNum);
	//ImGui::Text("Rifle Bullet2 : %d", bullets[1]->GetIsActive());
	//ImGui::Text("Rifle Bullet3 : %d", bullets[2]->GetIsActive());
	ImGui::Text("Rifle Bullet1 destination : %f, %f, %f", bullets[0]->GetDestination().x, bullets[0]->GetDestination().y, bullets[0]->GetDestination().z);
	ImGui::Text("Rifle Bullet1 origin : %f, %f, %f", bullets[0]->GetOrigin().x, bullets[0]->GetOrigin().y, bullets[0]->GetOrigin().z);
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

	if (curBulletNum >= bulletNum)
		curBulletNum = 0;
}
