#include "framework.h"
#include "Black.h"

Black::Black()
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(L"Resource/UI/Black.png", Vector2(1280, 720));
	_quad->SetPS(ADD_PS(L"Shader/TextureAlphaPS.hlsl"));
	_alphaBuffer = make_shared<AlphaBuffer>();
}

Black::~Black()
{
}

void Black::Update()
{
	_transform->Update();
	_alphaBuffer->Update();
}

void Black::PostRender()
{
	_transform->SetBuffer(0);
	_alphaBuffer->SetPSBuffer(5);
	_quad->Render();
}

void Black::FadeOut()
{
	_alphaBuffer->_data.alpha -= DELTA_TIME;
	if (_alphaBuffer->_data.alpha <= 0.0f)
		_alphaBuffer->_data.alpha = 0.0f;
}
