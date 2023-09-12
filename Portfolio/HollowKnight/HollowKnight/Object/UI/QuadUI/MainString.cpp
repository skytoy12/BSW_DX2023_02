#include "framework.h"
#include "MainString.h"

MainString::MainString(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
	//_quad->SetPS(ADD_PS(L"Shader/HPBarPS.hlsl"));
	_collider = make_shared<RectCollider>(size);

	_transform->SetParent(_collider->GetTransform());
}

MainString::~MainString()
{
}

void MainString::Update()
{
	_transform->Update();
	_collider->Update();
}

void MainString::PostRender()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}
