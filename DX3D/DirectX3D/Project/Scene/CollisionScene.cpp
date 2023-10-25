#include "Framework.h"
#include "CollisionScene.h"


CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		colliders.push_back(new ColliderSphere);
		colliders[i]->SetLabel("ColliderSphere" + to_string(i));
		colliders[i]->translation.x = 2 * i;
	}
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;
	colliders.clear();
}

void CollisionScene::Update()
{
	for (Collider* collider : colliders)
		collider->Update();

	if (colliders[0]->Collision(colliders[1]))
		colliders[0]->SetColor(1, 0, 0);
	else
		colliders[0]->SetColor(0, 1, 0);
}

void CollisionScene::PreRender()
{

}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
		collider->Render();
}

void CollisionScene::PostRender()
{
	for (Collider* collider : colliders)
		collider->Debug();
}
