#include "framework.h"
#include "HPFrame.h"

HPFrame::HPFrame()
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(L"Resource/UI/HP/HPFrame.png", Vector2(450.0f, 174.0f));
	//_quad->SetPS(ADD_PS(L"Shader/HPBarPS.hlsl"));

}

HPFrame::~HPFrame()
{
}

void HPFrame::Update()
{
	_transform->Update();
}

void HPFrame::PostRender()
{
	_transform->SetBuffer(0);
	_quad->Render();
}
