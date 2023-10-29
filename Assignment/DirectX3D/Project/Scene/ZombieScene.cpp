#include "Framework.h"
#include "ZombieScene.h"

ZombieScene::ZombieScene()
{
	groot = new Groot();

	terrain = new Terrain(L"LandScape/Wall.png", L"LandScape/Wall_specular.png", L"LandScape/Wall_normal.png", L"HeightMap/flat.png");

	zombie1 = new Zombie("copzombie_l_actisdato");
	zombie2 = new Zombie("Yaku J Ignite");
	zombie3 = new Zombie("Zombiegirl W Kurniawan");

	zombie1->translation += Vector3(250.0f, 0.0f, 250.0f);
	zombie2->translation += Vector3(500.0f, 0.0f, 500.0f);
	zombie3->translation += Vector3(0.0f, 0.0f, 500.0f);

	zombie1->SetTarget(groot);
	zombie2->SetTarget(groot);
	zombie3->SetTarget(groot);

	zombie1->SetSpeed(0.0f);
	zombie2->SetSpeed(10.0f);
	zombie3->SetSpeed(20.0f);

	Camera::GetInstance()->SetTarget(groot);
	terrain->scale *= 5.0f;
}

ZombieScene::~ZombieScene()
{
	delete groot;
	delete terrain;
}

void ZombieScene::Update()
{
	//CAMERA->rotation.y = angle - XM_PI;
	groot->Update();
	terrain->Update();

	zombie1->Update();
	zombie2->Update();
	zombie3->Update();

	zombie1->rotation.y = Angle(zombie1->GetGlobalPosition(), groot->GetGlobalPosition()) - XM_PI;
	zombie2->rotation.y = Angle(zombie2->GetGlobalPosition(), groot->GetGlobalPosition()) - XM_PI;
	zombie3->rotation.y = Angle(zombie3->GetGlobalPosition(), groot->GetGlobalPosition()) - XM_PI;

	groot->rotation.y = Angle(CAMERA->GetGlobalPosition(), groot->GetGlobalPosition()) - XM_PI;

	Ray ray = Camera::GetInstance()->ScreenPointToRay(mousePos);
	ray.direction *= -1;

	Contact contact = {};
	

	if (zombie1->GetCollider()->Collision(ray))
		zombie1->GetCollider()->SetColor(1, 0, 0);
	else
		zombie1->GetCollider()->SetColor(0, 1, 0);

	//ray.origin = CAMERA->translation;

	//ray.direction = groot->Forward();
	//ray.direction.y = 0.0f;
	
	//ray = Camera::GetInstance()->ScreenPointToRay(mousePos);

	//Attack();
}

void ZombieScene::PreRender()
{
}

void ZombieScene::Render()
{
	groot->Render();
	terrain->Render();


	zombie1->Render();
	zombie2->Render();
	zombie3->Render();
}

void ZombieScene::PostRender()
{
	terrain->Debug();
}

void ZombieScene::Attack()
{
	Ray ray1 = Camera::GetInstance()->ScreenPointToRay(mousePos);

	if (KEY_PRESS(VK_LBUTTON))
	{
		if (zombie1->GetCollider()->Collision(ray1))
		{
			zombie1->GetCollider()->SetColor(1.0f, 0.0f, 0.0f);
		}
		else
			zombie1->GetCollider()->SetColor(0.0f, 1.0f, 0.0f);

		if (zombie2->GetCollider()->Collision(ray1))
		{
			zombie2->GetCollider()->SetColor(1.0f, 0.0f, 0.0f);
		}
		else
			zombie2->GetCollider()->SetColor(0.0f, 1.0f, 0.0f);

		if (zombie3->GetCollider()->Collision(ray1))
		{
			zombie3->GetCollider()->SetColor(1.0f, 0.0f, 0.0f);
		}
		else
			zombie3->GetCollider()->SetColor(0.0f, 1.0f, 0.0f);
	}
	
}

void ZombieScene::CameraAngle()
{
	
		
}

float ZombieScene::Angle(Vector3 translation1, Vector3 translation2)
{
	Vector3 forward = translation1;
	forward.y = 0;
	Vector3 dir = translation2;
	dir.y = 0;
	dir = (dir - forward).GetNormalized();

	float angle = atan2(dir.x, dir.z);

	return angle;
}
