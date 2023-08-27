#include "Framework.h"
#include "RobotScene.h"

RobotScene::RobotScene()
{
	mainCube  = new Cube({ 0.0f, 0.2f, 0.5f, 1.0f });
	head      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	Lshoulder = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	Rshoulder = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	body      = new Cube({ 1.0f, 1.0f, 1.0f, 1.0f });
	Larm      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	Rarm      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	Lpelvis   = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	Rpelvis   = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	Lleg      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	Rleg      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	Reye      = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	Leye      = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	mouse1    = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	mouse2    = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });

	head     ->SetParent(mainCube);
	body     ->SetParent(mainCube);
	Lshoulder->SetParent(mainCube);
	Rshoulder->SetParent(mainCube);
	Lpelvis  ->SetParent(mainCube);
	Rpelvis  ->SetParent(mainCube);
	Larm     ->SetParent(Lshoulder);
	Rarm     ->SetParent(Rshoulder);   
	Lleg     ->SetParent(Lpelvis);
	Rleg     ->SetParent(Rpelvis);
	Leye     ->SetParent(head);
	Reye     ->SetParent(head);
	mouse1   ->SetParent(head);
	mouse2   ->SetParent(head);
}

RobotScene::~RobotScene()
{
}

void RobotScene::Update()
{
	CubeUpdate();
	CubeSize();
	CubePosition();
	CubeAngle();


	if (KEY_PRESS('1'))
	{
		Idle();
	}

	if (KEY_PRESS('2'))
	{
		smile();
	}

	if (KEY_PRESS('3'))
	{
		upset();
	}

	if (KEY_PRESS('E'))
	{
		mainCube->rotation.y += Time::Delta();
	}

	if (KEY_PRESS('Q'))
	{
		mainCube->rotation.y -= Time::Delta();
	}

	if (KEY_PRESS('W'))
	{
		mainCube->translation -= mainCube->Forward() * Time::Delta();

		
		Lshoulder->rotation.z = Ridan(0.0f);
		Rpelvis  ->rotation.z = Ridan(0.0f);
							
		Rshoulder->rotation.z = Ridan(0.0f);
		Lpelvis  ->rotation.z = Ridan(0.0f);

		Lshoulder->rotation.x += swing;
		Rpelvis  ->rotation.x += swing;

		Rshoulder->rotation.x -= swing;
		Lpelvis  ->rotation.x -= swing;
	}

	if (KEY_PRESS('S'))
	{
		mainCube->translation += mainCube->Forward() * Time::Delta();

		Lshoulder->rotation.z = Ridan(0.0f);
		Rpelvis->rotation.z = Ridan(0.0f);

		Rshoulder->rotation.z = Ridan(0.0f);
		Lpelvis->rotation.z = Ridan(0.0f);

		Lshoulder->rotation.x += swing;
		Rpelvis  ->rotation.x += swing;

		Rshoulder->rotation.x -= swing;
		Lpelvis  ->rotation.x -= swing;
	}

	if (KEY_PRESS('A'))
	{
		mainCube->translation -= mainCube->Right() * Time::Delta();

		Lshoulder->rotation.x = Ridan(0.0f);
		Rpelvis  ->rotation.x = Ridan(0.0f);

		Rshoulder->rotation.x = Ridan(0.0f);
		Lpelvis  ->rotation.x = Ridan(0.0f);

		Lshoulder->rotation.z += swing;
		Lpelvis  ->rotation.z += swing;
							
		Rshoulder->rotation.z -= swing;
		Rpelvis  ->rotation.z -= swing;
	}

	if (KEY_PRESS('D'))
	{
		mainCube->translation += mainCube->Right() * Time::Delta();

		Lshoulder->rotation.x = Ridan(0.0f);
		Rpelvis->rotation.x = Ridan(0.0f);

		Rshoulder->rotation.x = Ridan(0.0f);
		Lpelvis->rotation.x = Ridan(0.0f);

		Lshoulder->rotation.z += swing;
		Lpelvis->rotation.z += swing;

		Rshoulder->rotation.z -= swing;
		Rpelvis->rotation.z -= swing;
	}
}
void RobotScene::PreRender()
{
}

void RobotScene::Render()
{
	//mainCube  ->Render();
	head      ->Render();
	Lshoulder ->Render();
	Rshoulder ->Render();
	body      ->Render();
	Larm      ->Render();
	Rarm      ->Render();
	Lpelvis   ->Render();
	Rpelvis	  ->Render();
	Lleg      ->Render();
	Rleg      ->Render();
	Reye	  ->Render();
	Leye	  ->Render();
	mouse1	  ->Render();
	mouse2	  ->Render();
}

void RobotScene::PostRender()
{
	mainCube  ->Debug();
	head      ->Debug();
	Lshoulder ->Debug();
	Rshoulder ->Debug();
	body      ->Debug();
	Larm      ->Debug();
	Rarm      ->Debug();
	Lpelvis   ->Debug();
	Rpelvis   ->Debug();
	Lleg 	  ->Debug();
	Rleg	  ->Debug();
	Reye      ->Debug();
	Leye      ->Debug();
	mouse1    ->Debug();
	mouse2    ->Debug();
}

void RobotScene::CubeUpdate()
{
	mainCube ->Update();
	head     ->Update();
	body     ->Update();
	Lshoulder->Update();
	Rshoulder->Update();
	Larm     ->Update();
	Rarm     ->Update();
	Lpelvis  ->Update();
	Rpelvis  ->Update();
	Lleg     ->Update();
	Rleg     ->Update();
	Reye     ->Update();
	Leye     ->Update();
	mouse1   ->Update();
	mouse2   ->Update();
}

void RobotScene::CubeSize()
{
	head->scale.x = 0.5f;
	head->scale.y = 0.5f;
	head->scale.z = 0.5f;

	body->scale.x = 0.7f;
	body->scale.z = 0.7f;

	Lshoulder->scale.x = 0.3f;
	Lshoulder->scale.y = 0.3f;
	Lshoulder->scale.z = 0.3f;

	Rshoulder->scale.x = 0.3f;
	Rshoulder->scale.y = 0.3f;
	Rshoulder->scale.z = 0.3f;

	Larm->scale.x = 1.2f;
	Larm->scale.y = 2.5f;

	Rarm->scale.x = 1.2f;
	Rarm->scale.y = 2.5f;

	Lpelvis->scale.x = 0.3f;
	Lpelvis->scale.y = 0.3f;
	Lpelvis->scale.z = 0.3f;

	Rpelvis->scale.x = 0.3f;
	Rpelvis->scale.y = 0.3f;
	Rpelvis->scale.z = 0.3f;

	Lleg->scale.x = 1.2f;
	Lleg->scale.y = 2.5f;

	Rleg->scale.x = 1.2f;
	Rleg->scale.y = 2.5f;

	Leye->scale.x = 0.25f;
	Leye->scale.y = 0.03f;
	Leye->scale.z = 0.6f;

	Reye->scale.x = 0.25f;
	Reye->scale.y = 0.03f;
	Reye->scale.z = 0.6f;


	mouse1->scale.x = 0.25f;
	mouse1->scale.y = 0.03f;
	mouse1->scale.z = 0.6f;

	mouse2->scale.x = 0.25f;
	mouse2->scale.y = 0.03f;
	mouse2->scale.z = 0.6f;
}

void RobotScene::CubePosition()
{
	head->translation.y = 1.4f;

	body->translation.y = -0.5f;

	Lshoulder->translation.x = -1.5f;
	Lshoulder->translation.y = +0.2f;

	Rshoulder->translation.x = +1.5f;
	Rshoulder->translation.y = +0.2f;

	Larm->translation.x = -0.1f;
	Larm->translation.y = -4.0f;

	Rarm->translation.x = +0.1f;
	Rarm->translation.y = -4.0f;

	Lpelvis->translation.x = -0.6f;
	Lpelvis->translation.y = -2.1f;

	Rpelvis->translation.x = +0.6f;
	Rpelvis->translation.y = -2.1f;

	Lleg->translation.x = -0.1f;
	Lleg->translation.y = -4.0f;

	Rleg->translation.x = +0.1f;
	Rleg->translation.y = -4.0f;

	Leye->translation.x = -0.4f;
	Leye->translation.y = +0.2f;
	Leye->translation.z = -0.5f;

	Reye->translation.x = +0.4f;
	Reye->translation.y = +0.2f;
	Reye->translation.z = -0.5f;


	mouse1->translation.x = +0.2f;
	mouse1->translation.y = -0.4f;
	mouse1->translation.z = -0.5f;

	mouse2->translation.x = -0.2f;
	mouse2->translation.y = -0.4f;
	mouse2->translation.z = -0.5f;
}

void RobotScene::CubeAngle()
{

	if (Lshoulder->rotation.x > Ridan(60.0f))
		swing = -0.001f;
	else if (Lshoulder->rotation.x < Ridan(-60.0f))
		swing = 0.001f;

	if (Lshoulder->rotation.z > Ridan(0.0f))
		swing = -0.001f;
	else if (Lshoulder->rotation.z < Ridan(-60.0f))
		swing = 0.001f;
}

void RobotScene::ArmAngle()
{
}

void RobotScene::Idle()
{
	Leye->rotation.x = 0.0f;
	Leye->rotation.y = 0.0f;
	Leye->rotation.z = 0.0f;

	Reye->rotation.x = 0.0f;
	Reye->rotation.y = 0.0f;
	Reye->rotation.z = 0.0f;

	mouse1->rotation.x = 0.0f;
	mouse1->rotation.y = 0.0f;
	mouse1->rotation.z = 0.0f;

	mouse2->rotation.x = 0.0f;
	mouse2->rotation.y = 0.0f;
	mouse2->rotation.z = 0.0f;
}

void RobotScene::smile()
{
	Leye->rotation.x = 0.0f;
	Leye->rotation.y = 0.0f;
	Leye->rotation.z = Ridan(-150.0f);

	Reye->rotation.x = 0.0f;
	Reye->rotation.y = 0.0f;
	Reye->rotation.z = Ridan(150.0f);

	mouse1->rotation.x = 0.0f;
	mouse1->rotation.y = 0.0f;
	mouse1->rotation.z = 0.0f;

	mouse2->rotation.x = 0.0f;
	mouse2->rotation.y = 0.0f;
	mouse2->rotation.z = 0.0f;
}

void RobotScene::upset()
{
	Leye->rotation.x = 0.0f;
	Leye->rotation.y = 0.0f;
	Leye->rotation.z = Ridan(150.0f);

	Reye->rotation.x = 0.0f;
	Reye->rotation.y = 0.0f;
	Reye->rotation.z = Ridan(-150.0f);

	mouse1->rotation.x = 0.0f;
	mouse1->rotation.y = 0.0f;
	mouse1->rotation.z = 0.0f;

	mouse2->rotation.x = 0.0f;
	mouse2->rotation.y = 0.0f;
	mouse2->rotation.z = 0.0f;
}
