#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, Vector2 maxFrame, Vector2 size)
	: _maxFrame(maxFrame)
	, Quad(path, size)
{
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/SpritePS.hlsl");

	_frameBuffer = make_shared<FrameBuffer>();
	_frameBuffer->SetMaxFrame(maxFrame);
	_frameBuffer->SetCurFrame({ 0.0f, 0.0f });
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	_frameBuffer->Update();
}

void Sprite::Render()
{
	_frameBuffer->SetPSBuffer(0);
	Quad::Render();
}
