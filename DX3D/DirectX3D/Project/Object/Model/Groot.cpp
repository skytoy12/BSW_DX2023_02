#include "Framework.h"
#include "Groot.h"

Groot::Groot()
	:ModelAnimator("Groot")
{
	ReadClip("Sad Idle");
	ReadClip("Running Backward");
	ReadClip("Standing Melee Attack 360 High");
	CreateTexture();

	scale *= 0.04f;

	reader->GetMaterials()[0]->Load(L"Groot.mat");

	weapon = new Model("Dwarven_Axe");
	rightHand = new Transform();

	weapon->SetParent(rightHand);
	weapon->GetReader()->GetMaterials()[0]->Load(L"Dwarven_Axe");

	weapon->rotation.y = XMConvertToRadians(274);
	weapon->rotation.z = XMConvertToRadians(-79);

	weapon->translation = { -50.630f, 68.640f, -20.580f };

	clips[ATTACK]->SetEndEvent(bind(&Groot::SetClip, this, IDLE), 0.7f);

	hpBar = new ProgressBar(L"UI/hp_bar.png", L"UI/hp_bar_BG.png");
	hpBar->SetLabel("HP Bar");
	hpBar->scale.x *= 0.5f;
}

Groot::~Groot()
{
	delete weapon;
	delete rightHand;

	delete hpBar;
}

void Groot::Update()
{
	ModelAnimator::Update();
	Transform::Update();
	weapon->Update();
	rightHand->Update();

	hpBar->Update();
	hpBar->translation = Camera::GetInstance()->WorldToScreenPoint(this->globalPosition + V_UP * 10.0f);
	//hpBar->translation.y += 200.0f;

	if (KEY_DOWN('1'))
		PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		PlayClip(2, speed, takeTime);

	//Move();
	Attack();

	UpdateRightHand();
}

void Groot::Render()
{
	ModelAnimator::Render();
	weapon->Render();
}

void Groot::Debug()
{
	ModelAnimator::reader->Debug();
	ModelAnimator::Debug();
	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);

	ImGui::Text("DeltaTime : %f", Time::Delta());

	weapon->Debug();
	static float value = 1.0f;
	hpBar->SetValue(value);
	ImGui::SliderFloat("HP", &value, 0.0f, 1.0f);
}

void Groot::PostRender()
{
	Debug();
	hpBar->Render();
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
	}
}
