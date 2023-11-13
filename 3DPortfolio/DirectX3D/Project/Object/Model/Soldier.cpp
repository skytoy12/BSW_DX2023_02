#include "Framework.h"
#include "Soldier.h"

Soldier::Soldier()
	: ModelAnimator("EliteFederationSoldier")
{
	ReadClip("Rifle/Rifle Idle");
	ReadClip("Rifle/Rifle Run");
	ReadClip("Rifle/Rifle Walk");

	ReadClip("Idle/Breathing Idle");
	ReadClip("Idle/Running");
	ReadClip("Idle/Walking");

	CreateTexture();
	reader->GetMaterials()[0]->SetDiffuseMap(L"Model/EliteFederationSoldier/elite_pmc_lowerbody_a_col.png");

}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
	ModelAnimator::Update();
	Transform::Update();

	if (KEY_DOWN('1'))
		PlayClip(0, animSpeed, takeTime);

	if (KEY_DOWN('2'))
		PlayClip(1, animSpeed, takeTime);

	if (KEY_DOWN('3'))
		PlayClip(2, animSpeed, takeTime);

	if (KEY_DOWN('4'))
		PlayClip(3, animSpeed, takeTime);

	if (KEY_DOWN('5'))
		PlayClip(4, animSpeed, takeTime);

	if (KEY_DOWN('6'))
		PlayClip(5, animSpeed, takeTime);
	
	Move();

	if (isMove() == true)
	{
		SetAngle();
		SetClip(RUN);
	}
	else
		SetClip(IDLE);
}

void Soldier::Render()
{
	ModelAnimator::Render();
}

void Soldier::Debug()
{
	ModelAnimator::reader->Debug();
	ModelAnimator::Debug();

	ImGui::Text("curPos = %f, %f, %f", curPos.x, curPos.y, curPos.z);
	ImGui::Text("oldPos = %f, %f, %f", oldPos.x, oldPos.y, oldPos.z);
}

void Soldier::PostRender()
{
	Debug();
}

void Soldier::SetAngle()
{
	Vector3 temp = this->GetGlobalPosition();
	temp.y = 0;
	Vector3 dir = destination;
	dir.y = 0;

	dir = (dir - temp).GetNormalized();

	float angle = atan2(dir.x, dir.z) - XM_PI;

	float isLeft = abs(angle) + abs(this->rotation.y);

	if (isLeft < XM_PI)
	{
		this->rotation.y = LERP(this->rotation.y, angle, rotDamping * Time::Delta());
	}
	else if (isLeft > XM_PI)
	{
		angle = angle - XM_2PI;
		this->rotation.y = LERP(this->rotation.y, angle, rotDamping * Time::Delta());
	}

}

void Soldier::Move()
{
	int temp1 = abs((int)destination.x - (int)this->translation.x);
	int temp2 = abs((int)destination.x - (int)this->translation.x);
	int temp3 = abs((int)destination.x - (int)this->translation.x);

	if (temp1 == 0 && temp2 == 0 && temp3 == 0)
		return;

	Vector3 dir = destination - this->translation;
	dir = dir.GetNormalized();

	translation += dir * moveSpeed * Time::Delta();
}


void Soldier::SetClip(SoliderState type)
{
	if (type == curState)
		return;
	curState = type;
	oldState = curState;

	PlayClip(curState);
}

bool Soldier::isMove()
{
	oldPos = curPos;
	Transform::UpdateWorld();
	curPos = this->GetGlobalPosition();

	float a = abs(oldPos.x - curPos.x);
	float b = abs(oldPos.y - curPos.y);
	float c = abs(oldPos.z - curPos.z);

	if (a <= FLT_EPSILON && b <= FLT_EPSILON && c <= FLT_EPSILON)
		return false;
	else
		return true;
}
