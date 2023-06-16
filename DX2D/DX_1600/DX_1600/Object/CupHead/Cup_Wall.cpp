#include "framework.h"
#include "Cup_Wall.h"

Cup_Wall::Cup_Wall()
{
	_leftWall = make_shared<RectCollider>(Vector2(10, WIN_HEIGHT));
	_leftWall->SetPosition(Vector2(0, WIN_HEIGHT / 2));

	_rightWall = make_shared<RectCollider>(Vector2(10, WIN_HEIGHT));
	_rightWall->SetPosition(Vector2(WIN_WIDTH - 15, WIN_HEIGHT / 2));
}

Cup_Wall::~Cup_Wall()
{
}

void Cup_Wall::Update()
{
	_leftWall->Update();
	_rightWall->Update();
}

void Cup_Wall::Render()
{
	_leftWall->Render();
	_rightWall->Render();
}
