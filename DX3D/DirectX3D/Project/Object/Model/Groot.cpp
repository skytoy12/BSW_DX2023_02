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

	weapon = new Sphere(30);
	rightHand = new Transform();

	weapon->SetParent(rightHand);
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

	if (KEY_DOWN('1'))
		PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		PlayClip(2, speed, takeTime);

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

	weapon->Debug();
}

void Groot::UpdateRightHand()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:RightHand");

	rightHand->GetWorld() = GetTransformByNode(nodeIndex) * world;
}
