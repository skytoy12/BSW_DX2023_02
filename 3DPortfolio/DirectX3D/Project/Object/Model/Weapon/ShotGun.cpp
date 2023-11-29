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
		string a = "bullet" + to_string(i);
		bullet->SetLabel(a);

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
	{
		isAttack = false;
		for (Bullet* bullet : bullets)
			bullet->SetIsActive(false);
	}
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
	for (Bullet* bullet : bullets)
		bullet->Debug();
}

void ShotGun::Debug()
{
	ImGui::Text("origin : %f, %f, %f", origin.x, origin.y, origin.z);
	ImGui::Text("isAttack : %d", isAttack);
	ImGui::Text("dir : %f, %f, %f", dir.x, dir.y, dir.z);

	ImGui::Text("bullet1 origin : %f, %f, %f", bullets[0]->GetOrigin().x, bullets[0]->GetOrigin().y, bullets[0]->GetOrigin().z);
	ImGui::Text("bullet1 destination : %f, %f, %f", bullets[0]->GetDestination().x, bullets[0]->GetDestination().y, bullets[0]->GetDestination().z);

	ImGui::Text("bullet2 origin : %f, %f, %f", bullets[1]->GetOrigin().x, bullets[1]->GetOrigin().y, bullets[1]->GetOrigin().z);
	ImGui::Text("bullet2 destination : %f, %f, %f", bullets[1]->GetDestination().x, bullets[1]->GetDestination().y, bullets[1]->GetDestination().z);
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
		Vector3 destination = bullet->GetOrigin() + (dir * bullet->GetRange());
		bullet->SetDestination(destination);
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

void ShotGun::SetBulletActive(bool value)
{
	for (Bullet* bullet : bullets)
		bullet->SetIsActive(value);
}
