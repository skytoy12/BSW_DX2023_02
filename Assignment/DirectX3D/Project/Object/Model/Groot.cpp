#include "Framework.h"
#include "Groot.h"

Groot::Groot()
	:ModelAnimator("Groot")
{
	ReadClip("Sad Idle");
	ReadClip("Running Backward");
	ReadClip("Standing Melee Attack 360 High");
	CreateTexture();

	scale *= 0.01f;

	reader->GetMaterials()[0]->Load(L"Groot.mat");

	weapon = new Model("Dwarven_Axe");
	rightHand = new Transform();

	weapon->SetParent(rightHand);
	weapon->GetReader()->GetMaterials()[0]->Load(L"Dwarven_Axe");

	weapon->rotation.y = XMConvertToRadians(274);
	weapon->rotation.z = XMConvertToRadians(-79);

	weapon->translation = { -50.630f, 68.640f, -20.580f };

	clips[ATTACK]->SetEndEvent(bind(&Groot::SetClip, this, IDLE), 0.7f);

	for (int i = 0; i < 30; i++)
	{
		Bullet* bullet = new Bullet();

		bullets.push_back(bullet);
	}
}

Groot::~Groot()
{
	delete weapon;
	delete rightHand;

	for (Bullet* bullet : bullets)
		delete bullet;
	bullets.clear();
}

void Groot::Update()
{
	ModelAnimator::Update();
	Transform::Update();
	weapon->Update();
	rightHand->Update();

	if (KEY_DOWN('1'))
		PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		PlayClip(2, speed, takeTime);

	Move();
	Attack();

	UpdateRightHand();

	for (Bullet* bullet : bullets)
	{
		if (bullet->isActive == false)
			bullet->SetDir(-Forward());
	}

	for (Bullet* bullet : bullets)
	{
		if (bullet->isActive == true)
		{
			float distance = (bullet->translation - this->translation).Length();

			if (distance > 1000.0f)
				bullet->isActive == false;
		}
	}

	for (Bullet* bullet : bullets)
		bullet->Update();
}

void Groot::Render()
{
	ModelAnimator::Render();
	weapon->Render();

	for (Bullet* bullet : bullets)
		bullet->Render();
}

void Groot::Debug()
{
	ModelAnimator::reader->Debug();
	ModelAnimator::Debug();
	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);

	ImGui::Text("DeltaTime : %f", Time::Delta());

	weapon->Debug();
}

void Groot::UpdateRightHand()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:RightHand");

	rightHand->GetWorld() = GetTransformByNode(nodeIndex) * world;
}

void Groot::SetClip(AnimState state)
{
	if (curState != state)
	{
		PlayClip(state);
		curState = state;
	}
}

void Groot::Move()
{
	if (KEY_PRESS('W'))
	{
		translation -= Forward() * moveSpeed * Time::Delta();
		SetClip(RUN);
	}

	if (KEY_PRESS('S'))
	{
		translation -= Backward() * moveSpeed * Time::Delta();
		SetClip(RUN);
	}

	if (KEY_UP('W') || KEY_UP('S'))
		SetClip(IDLE);

	if (KEY_PRESS('A'))
	{
		rotation.y -= rotSpeed * Time::Delta();
	}

	if (KEY_PRESS('D'))
	{
		rotation.y += rotSpeed * Time::Delta();
	}
}

void Groot::Attack()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		SetClip(ATTACK);

		auto bulletiter = std::find_if(bullets.begin(), bullets.end(), [](const Bullet* obj)->bool {return !obj->isActive; });

		if (bulletiter == bullets.end())
			return;
		(*bulletiter)->Shoot(translation + Vector3(0.0f, 10.0f, 0.0f));
	}

}
