#include "Framework.h"
#include "RobotScene.h"

RobotScene::RobotScene()
{
	robot = new Robot();
}

RobotScene::~RobotScene()
{
	delete robot;
}

void RobotScene::Update()
{
	robot->Update();
}

void RobotScene::PreRender()
{
}

void RobotScene::Render()
{
	robot->Render();
}

void RobotScene::PostRender()
{
}

