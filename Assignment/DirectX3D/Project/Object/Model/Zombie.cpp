#include "Framework.h"
#include "Zombie.h"


Zombie::Zombie(string name)
	:ModelAnimator(name)
{
	if(name == "copzombie_l_actisdato")
		ReadClip("Hip Hop Dancing");
	if (name == "Yaku J Ignite")
		ReadClip("Walking");
	if (name == "Zombiegirl W Kurniawan")
		ReadClip("Zombie Run");

	model = new Transform();

	collider = new ColliderBox(Vector3(50, 200, 50));

	CreateTexture();

	collider->SetParent(model);


	scale *= 0.08f;
}

Zombie::~Zombie()
{
	delete collider;
}

void Zombie::Update()
{
	ModelAnimator::Update();
	Transform::Update();
	collider->Update();
	model->Update();

	UpdateCollider();

	Move();
}

void Zombie::Render()
{
	ModelAnimator::Render();
	collider->Render();
}

void Zombie::Debug()
{
}

void Zombie::UpdateCollider()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:Hips");

	model->GetWorld() = GetTransformByNode(nodeIndex) * world;
}

void Zombie::Move()
{
	if (target == nullptr)
		return;

	dir = target->translation - translation;
	dir.y = 0.0f;

	dir.Normalize();

	translation += dir * moveSpeed * Time::Delta();
}

void Zombie::Attack()
{
}
