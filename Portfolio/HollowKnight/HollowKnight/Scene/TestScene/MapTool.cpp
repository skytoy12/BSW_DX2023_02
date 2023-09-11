#include "framework.h"
#include "MapTool.h"

MapTool::MapTool()
{
	_collider = make_shared<CircleCollider>(50.0f);
	_collider->SetPosition(Vector2(0, 0));
}

MapTool::~MapTool()
{
}

void MapTool::Update()
{
	_collider->Update();
}

void MapTool::Render()
{
	_collider->Render();
}

void MapTool::PostRender()
{
}

void MapTool::PreRender()
{
}
