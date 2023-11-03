#include "Framework.h"
#include "Soldier.h"

Soldier::Soldier()
	: ModelAnimator("EliteFederationSoldier")
{
	ReadClip("Rifle Idle");
	CreateTexture();
	reader->GetMaterials()[0]->SetDiffuseMap(L"Model/EliteFederationSoldier/elite_pmc_alpha_ab_col.png");

	int a = 10;
}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
	ModelAnimator::Update();
	Transform::Update();
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
