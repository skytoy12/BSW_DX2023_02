#include "Framework.h"
#include "Robot.h"

Robot::Robot()
{
	CreateRobot();
	cubes[MAIN]->translation = Vector3(100, 90, 10);
}

Robot::~Robot()
{
	for (Cube* cube : cubes)
		delete cube;

	cubes.clear();
}

void Robot::Update()
{
	for (Cube* cube : cubes)
		cube->Update();

	CubeSize();
	CubePosition();
	CubeAngle();

	if (KEY_PRESS('I'))
	{
		SetPosition(Vector3(120, 90, -10));
	}

	if (KEY_PRESS('E'))
	{
		cubes[MAIN]->rotation.y += Time::Delta();
	}

	if (KEY_PRESS('Q'))
	{
		cubes[MAIN]->rotation.y -= Time::Delta();
	}

	if (KEY_PRESS('W'))
	{
		cubes[MAIN]->translation -= cubes[MAIN]->Forward() * Time::Delta();


		cubes[LSHOULDER]->rotation.z = Ridan(0.0f);
		cubes[RPELVIS]->rotation.z = Ridan(0.0f);

		cubes[RSHOULDER]->rotation.z = Ridan(0.0f);
		cubes[LPELVIS]->rotation.z = Ridan(0.0f);

		cubes[LSHOULDER]->rotation.x += swing;
		cubes[RPELVIS]->rotation.x += swing;

		cubes[RSHOULDER]->rotation.x -= swing;
		cubes[LPELVIS]->rotation.x -= swing;
	}

	if (KEY_PRESS('S'))
	{
		cubes[MAIN]->translation += cubes[MAIN]->Forward() * Time::Delta();

		cubes[LSHOULDER]->rotation.z = Ridan(0.0f);
		cubes[RPELVIS]->rotation.z = Ridan(0.0f);

		cubes[RSHOULDER]->rotation.z = Ridan(0.0f);
		cubes[LPELVIS]->rotation.z = Ridan(0.0f);

		cubes[LSHOULDER]->rotation.x += swing;
		cubes[RPELVIS]->rotation.x += swing;

		cubes[RSHOULDER]->rotation.x -= swing;
		cubes[LPELVIS]->rotation.x -= swing;
	}

	if (KEY_PRESS('A'))
	{
		cubes[MAIN]->translation -= cubes[MAIN]->Right() * Time::Delta();

		cubes[LSHOULDER]->rotation.x = Ridan(0.0f);
		cubes[RPELVIS]->rotation.x = Ridan(0.0f);

		cubes[RSHOULDER]->rotation.x = Ridan(0.0f);
		cubes[LPELVIS]->rotation.x = Ridan(0.0f);

		cubes[LSHOULDER]->rotation.z += swing;
		cubes[LPELVIS] ->rotation.z += swing;

		cubes[RSHOULDER]->rotation.z -= swing;
		cubes[RPELVIS]->rotation.z -= swing;
	}

	if (KEY_PRESS('D'))
	{
		cubes[MAIN]->translation += cubes[MAIN]->Right() * Time::Delta();

		cubes[LSHOULDER]->rotation.x = Ridan(0.0f);
		cubes[RPELVIS]->rotation.x = Ridan(0.0f);

		cubes[RSHOULDER]->rotation.x = Ridan(0.0f);
		cubes[LPELVIS]->rotation.x = Ridan(0.0f);

		cubes[LSHOULDER]->rotation.z += swing;
		cubes[LPELVIS]->rotation.z += swing;

		cubes[RSHOULDER]->rotation.z -= swing;
		cubes[RPELVIS]->rotation.z -= swing;
	}
}

void Robot::Render()
{
	for (Cube* cube : cubes)
		cube->Render();
}

void Robot::PostRender()
{
	ImGui::Text("main scale : %.1f, %.1f, %.1f", cubes[MAIN]->scale.x, cubes[MAIN]->scale.y, cubes[MAIN]->scale.z);
	ImGui::Text("head scale : %.1f, %.1f, %.1f", cubes[HEAD]->scale.x, cubes[HEAD]->scale.y, cubes[HEAD]->scale.z);
}

void Robot::CreateRobot()
{
	cubes.resize(15);

	cubes[MAIN]      = new Cube({ 0.0f, 0.2f, 0.5f, 1.0f });
	cubes[HEAD]      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	cubes[LSHOULDER] = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	cubes[RSHOULDER] = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	cubes[LARM]      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	cubes[RARM]      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	cubes[LPELVIS]   = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	cubes[RPELVIS]   = new Cube({ 0.2f, 0.2f, 0.2f, 1.0f });
	cubes[LLEG]      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	cubes[RLEG]      = new Cube({ 0.3f, 0.0f, 0.0f, 1.0f });
	cubes[LEYE]      = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	cubes[REYE]      = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	cubes[MOUSE1]    = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	cubes[MOUSE2]    = new Cube({ 0.0f, 0.3f, 0.0f, 1.0f });
	cubes[BODY]      = new Cube({ 1.0f, 1.0f, 1.0f, 1.0f });

	cubes[HEAD]->SetParent(cubes[MAIN]);
	cubes[BODY]->SetParent(cubes[MAIN]);
	cubes[LSHOULDER]->SetParent(cubes[MAIN]);
	cubes[RSHOULDER]->SetParent(cubes[MAIN]);
	cubes[LPELVIS]->SetParent(cubes[MAIN]);
	cubes[RPELVIS]->SetParent(cubes[MAIN]);
	cubes[LARM]->SetParent(cubes[LSHOULDER]);
	cubes[RARM]->SetParent(cubes[RSHOULDER]);
	cubes[LLEG]->SetParent(cubes[LPELVIS]);
	cubes[RLEG]->SetParent(cubes[RPELVIS]);
	cubes[LEYE]->SetParent(cubes[HEAD]);
	cubes[REYE]->SetParent(cubes[HEAD]);
	cubes[MOUSE1]->SetParent(cubes[HEAD]);
	cubes[MOUSE2]->SetParent(cubes[HEAD]);

}

void Robot::CubeUpdate()
{
}

void Robot::CubeSize()
{
	cubes[HEAD]->scale.x = 0.5f;
	cubes[HEAD]->scale.y = 0.5f;
	cubes[HEAD]->scale.z = 0.5f;

	cubes[BODY]->scale.x = 0.7f;
	cubes[BODY]->scale.z = 0.7f;
	cubes[BODY]->scale.y = 1.0f;

	cubes[LSHOULDER]->scale.x = 0.3f;
	cubes[LSHOULDER]->scale.y = 0.3f;
	cubes[LSHOULDER]->scale.z = 0.3f;

	cubes[RSHOULDER]->scale.x = 0.3f;
	cubes[RSHOULDER]->scale.y = 0.3f;
	cubes[RSHOULDER]->scale.z = 0.3f;

	cubes[LARM]->scale.x = 1.2f;
	cubes[LARM]->scale.y = 2.5f;
	cubes[LARM]->scale.z = 1.0f;

	cubes[RARM]->scale.x = 1.2f;
	cubes[RARM]->scale.y = 2.5f;
	cubes[RARM]->scale.z = 1.0f;

	cubes[LPELVIS]->scale.x = 0.3f;
	cubes[LPELVIS]->scale.y = 0.3f;
	cubes[LPELVIS]->scale.z = 0.3f;

	cubes[RPELVIS]->scale.x = 0.3f;
	cubes[RPELVIS]->scale.y = 0.3f;
	cubes[RPELVIS]->scale.z = 0.3f;

	cubes[LLEG]->scale.x = 1.2f;
	cubes[LLEG]->scale.y = 2.5f;

	cubes[LLEG]->scale.z = 1.0f;

	cubes[RLEG]->scale.x = 1.2f;
	cubes[RLEG]->scale.y = 2.5f;

	cubes[RLEG]->scale.z = 1.0f;

	cubes[LEYE]->scale.x = 0.25f;
	cubes[LEYE]->scale.y = 0.03f;
	cubes[LEYE]->scale.z = 0.6f ;

	cubes[REYE]->scale.x = 0.25f;
	cubes[REYE]->scale.y = 0.03f;
	cubes[REYE]->scale.z = 0.6f ;


	cubes[MOUSE1]->scale.x = 0.25f;
	cubes[MOUSE1]->scale.y = 0.03f;
	cubes[MOUSE1]->scale.z = 0.6f ;

	cubes[MOUSE2]->scale.x = 0.25f;
	cubes[MOUSE2]->scale.y = 0.03f;
	cubes[MOUSE2]->scale.z = 0.6f ;
}

void Robot::CubePosition()
{
	cubes[HEAD]->translation.y = 1.4f;

	cubes[BODY]->translation.y = -0.5f;

	cubes[LSHOULDER]->translation.x = -1.5f;
	cubes[LSHOULDER]->translation.y = +0.2f;

	cubes[RSHOULDER]->translation.x = +1.5f;
	cubes[RSHOULDER]->translation.y = +0.2f;

	cubes[LARM]->translation.x = -0.1f;
	cubes[LARM]->translation.y = -4.0f;

	cubes[RARM]->translation.x = +0.1f;
	cubes[RARM]->translation.y = -4.0f;

	cubes[LPELVIS]->translation.x = -0.6f;
	cubes[LPELVIS]->translation.y = -2.1f;

	cubes[RPELVIS]->translation.x = +0.6f;
	cubes[RPELVIS]->translation.y = -2.1f;

	cubes[LLEG]->translation.x = -0.1f;
	cubes[LLEG]->translation.y = -4.0f;

	cubes[RLEG]->translation.x = +0.1f;
	cubes[RLEG]->translation.y = -4.0f;

	cubes[LEYE]->translation.x = -0.4f;
	cubes[LEYE]->translation.y = +0.2f;
	cubes[LEYE]->translation.z = -0.5f;

	cubes[REYE]->translation.x = +0.4f;
	cubes[REYE]->translation.y = +0.2f;
	cubes[REYE]->translation.z = -0.5f;


	cubes[MOUSE1]->translation.x = +0.2f;
	cubes[MOUSE1]->translation.y = -0.4f;
	cubes[MOUSE1]->translation.z = -0.5f;

	cubes[MOUSE2]->translation.x = -0.2f;
	cubes[MOUSE2]->translation.y = -0.4f;
	cubes[MOUSE2]->translation.z = -0.5f;
}

void Robot::CubeAngle()
{
	if (cubes[LSHOULDER]->rotation.x > Ridan(60.0f))
		swing = -0.001f;
	else if (cubes[LSHOULDER]->rotation.x < Ridan(-60.0f))
		swing = 0.001f;

	if (cubes[LSHOULDER]->rotation.z > Ridan(0.0f))
		swing = -0.001f;
	else if (cubes[LSHOULDER]->rotation.z < Ridan(-60.0f))
		swing = 0.001f;
}

void Robot::SetPosition(Vector3 pos)
{
	cubes[MAIN]->translation = pos;
}

//void Robot::SetPosition(Vector3 pos)
//{
//	pos.y += Height;
//	cubes[MAIN]->translation = pos;
//}

