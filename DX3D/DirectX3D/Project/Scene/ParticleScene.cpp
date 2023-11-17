#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	collider = new ColliderSphere(50);

	//particle = new Sprite(L"Effect/greenCore_4x4.png",Vector2(30.0f, 30.0f), 4, 4, true);
	//particle = new Spark(L"Effect/star.png", true);
	particle = new Rain(L"Effect/Rain.png");
	particle->Play({0, 0, 0});
}

ParticleScene::~ParticleScene()
{
	delete collider;
	delete particle;
}

void ParticleScene::Update()
{
	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	Ray ray = CAMERA->ScreenPointToRay(mousePos);

	//	Contact contact;

	//	if (collider->Collision(ray, &contact))
	//	{
	//		particle->Play(contact.hitpoint);
	//	}
	//}

	collider->Update();
	particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
	//collider->Render();
	particle->Render();
}

void ParticleScene::PostRender()
{
	particle->Debug();
}

