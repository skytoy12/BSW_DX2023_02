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
}

void Soldier::Render()
{
	ModelAnimator::Render();
}

void Soldier::Debug()
{
	ModelAnimator::reader->Debug();
	ModelAnimator::Debug();
}

void Soldier::PostRender()
{
	Debug();
}

void Soldier::Move()
{
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
	return false;
}
