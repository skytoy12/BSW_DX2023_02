#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	soldier = new Soldier();

	//terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/flat.png");
	terrain = new TerrainEditor();

	//for (int i = 0; i < 20; i++)
	//{
	//	Bullet* bullet = new Bullet();
	//	bullet->SetTarget(soldier);

	//	bullets.push_back(bullet);
	//}


	terrain->SetLabel("terrain1");

	terrain->translation.x = -50;
	terrain->translation.z = -50;

	Camera::GetInstance()->SetTarget(soldier);
	
	//model = new  ModelAnimatorInstancing("PoliceZombie");
	//model->ReadClip("Zombie Attack");
	//model->ReadClip("Zombie Running");

	//for (float z = 0; z < 10; z++)
	//{
	//	for (float x = 0; x < 10; x++)
	//	{
	//		Transform* transform = model->Add();

	//		transform->translation = { x * 10, 0, z * 10 };
	//		transform->scale *= 0.05f;
	//	}
	//}
}

TestScene::~TestScene()
{
	delete soldier;
	delete groot;

	//for (Bullet* bullet : bullets)
	//	delete bullet;
	//bullets.clear();

	delete terrain;
	delete model;
}

void TestScene::Update()
{
	soldier->Update();

	terrain->Update();
	//for (Bullet* bullet : bullets)
	//	bullet->Update();

	//for (Bullet* bullet : bullets)
	//{
	//	Vector3 dir = pos;
	//	dir.y = 5.0f;
	//	dir.x = dir.x + Random(0.1f, 0.3f);
	//	dir.y = dir.y + Random(0.1f, 0.3f);
	//	dir.z = dir.z + Random(0.1f, 0.3f);

	//	dir = dir - bullet->GetOrigin();
	//	dir.Normalize();
	//	bullet->SetDestination(dir);
	//}

	if (KEY_DOWN('L'))
	{
		isFree = !isFree;
	}
	if (isFree == true)
		Camera::GetInstance()->SetTarget(nullptr);
	else
		Camera::GetInstance()->SetTarget(soldier);


	if(KEY_PRESS(VK_RBUTTON))
		terrain->Picking(&pos);

	soldier->SetDestination(pos);
	//model->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	soldier->Render();

	terrain->Render();
	//model->Render();
	//for (Bullet* bullet : bullets)
	//	bullet->Render();
}

void TestScene::PostRender()
{
	soldier->PostRender();

	terrain->Debug();
	ImGui::Text("MousePos : %f, %f, %f", mousePos.x, mousePos.y, mousePos.z);
	//ImGui::SliderInt("InstanceIndex", &instanceIndex, 0, 100);
	//ImGui::SliderInt("ClipIndex", &clip, 0, 1);
	//if (ImGui::Button("Play"))
	//	model->PlayClip(instanceIndex, clip);
	//model->Debug();
}

