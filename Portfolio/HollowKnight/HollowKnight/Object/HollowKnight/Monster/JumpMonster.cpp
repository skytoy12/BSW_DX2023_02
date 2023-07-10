#include "framework.h"
#include "JumpMonster.h"

JumpMonster::JumpMonster()
{
	_col = make_shared<CircleCollider>(25);
	_transform->SetParent(_col->GetTransform());
}

JumpMonster::~JumpMonster()
{
}

void JumpMonster::Update()
{
	Gravity();
	_col->Update();
}

void JumpMonster::Render()
{
	_col->Render();
}

void JumpMonster::PostRender()
{
}

void JumpMonster::Attack()
{
}
