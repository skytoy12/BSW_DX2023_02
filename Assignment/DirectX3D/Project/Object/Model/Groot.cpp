#include "Framework.h"
#include "Groot.h"

Groot::Groot()
	:ModelAnimator("Groot")
{
	ReadClip("Running Backward");
	ReadClip("Sad Idle");
	ReadClip("Standing Melee Attack 360 High");
	CreateTexture();
	
	scale *= 0.2f;

	reader->GetMaterials()[0]->Load(L"Groot.mat");

	weapon = new Model("Ax");
	rightHand = new Transform();

	weapon->SetParent(rightHand);
	weapon->scale *= 30.0f;

	weapon->rotation.x = 4.4f;
	weapon->rotation.y = 6.2f;
	weapon->rotation.z = 4.4f;

	weapon->translation.x = -19.0f;
	weapon->translation.y = -7.0f;
	weapon->translation.z = -57.0f;

	PlayClip(type, speed, takeTime);

	SetEndEvent(std::bind(&Groot::EndEvent, this));
}

Groot::~Groot()
{
	delete weapon;
	delete rightHand;
}

void Groot::Update()
{
	ModelAnimator::Update();
	weapon->Update();
	rightHand->Update();

	if (KEY_DOWN(VK_SPACE))
		PlayClip(ATTACK, speed, takeTime);

	if (KEY_DOWN('W'))
	{
		PlayClip(RUN, speed, takeTime);
		rotation.y = 0.0f * XM_PI / 180.0f;
	}

	if (KEY_UP('W'))
		PlayClip(IDLE, speed, takeTime);

	if (KEY_PRESS('W'))
		translation.z -= 0.05f;

	if (KEY_DOWN('S'))
	{
		PlayClip(RUN, speed, takeTime);
		rotation.y = 180.0f * XM_PI / 180.0f;
	}

	if (KEY_UP('S'))
		PlayClip(IDLE, speed, takeTime);

	if (KEY_PRESS('S'))
		translation.z += 0.05f;

	if (KEY_DOWN('A'))
	{
		PlayClip(RUN, speed, takeTime);
		rotation.y = 270.0f * XM_PI / 180.0f;
	}


	if (KEY_UP('A'))
		PlayClip(IDLE, speed, takeTime);

	if (KEY_PRESS('A'))
		translation.x += 0.05f;

	if (KEY_DOWN('D'))
	{
		PlayClip(RUN, speed, takeTime);
		rotation.y = 90.0f * XM_PI / 180.0f;
	}

	if (KEY_UP('D'))
		PlayClip(IDLE, speed, takeTime);

	if (KEY_PRESS('D'))
		translation.x -= 0.05f;

	//if (KEY_DOWN('1'))
	//	PlayClip(0, speed, takeTime);

	//if (KEY_DOWN('2'))
	//	PlayClip(1, speed, takeTime);

	//if (KEY_DOWN('3'))
	//	PlayClip(2, speed, takeTime);

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
	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);

	ImGui::SliderFloat("x", &x, -100.0f, 100.0f);
	ImGui::SliderFloat("y", &y, -100.0f, 100.0f);
	ImGui::SliderFloat("z", &z, -100.0f, 100.0f);

	weapon->Debug();
}

void Groot::UpdateRightHand()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:RightHand");

	rightHand->GetWorld() = GetTransformByNode(nodeIndex) * world;
}

void Groot::EndEvent()
{
	if (!KEY_PRESS('W') && !KEY_PRESS('S') && !KEY_PRESS('A') && !KEY_PRESS('D'))
	{
		PlayClip(IDLE, speed, takeTime);
	}
}
