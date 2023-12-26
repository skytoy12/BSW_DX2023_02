#include "Framework.h"
#include "ShotGun.h"

ShotGun::ShotGun(string file)
	:Gun(file)
{
	for (int i = 0; i < 16; i++)
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
	Transform::Debug();

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

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			int a = (x * 4) + y;
			Vector3 tempx = (x - 2) * Right() * 0.04f;
			Vector3 tempy = (y - 2) * Up() * 0.04f;
			dir += tempx;
			dir += tempy;
			dir.Normalize();
			bullets[a]->SetDestination(dir);
			Vector3 destination = bullets[a]->GetOrigin() + (dir * bullets[a]->GetRange());
			bullets[a]->SetDestination(destination);
		}
	}

	for (Bullet* bullet : bullets)
		bullet->Update();
}

void ShotGun::SetBulletActive(bool value)
{
	for (Bullet* bullet : bullets)
		bullet->SetIsActive(value);
}
