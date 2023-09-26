#include "framework.h"
#include "BackGround.h"
BackGround::BackGround(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
	_quad->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));
	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.selected = 2;
	_filterBuffer->_data.Value2 = 1;
	_filterBuffer->_data.imageSize = _quad->GetImageSize();
	_filterBuffer->_data.radialCenter = Vector2(0.5f, 0.5f);
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
	_transform->Update();
	_filterBuffer->Update();
}

void BackGround::Render()
{
	_transform->SetBuffer(0);
	_filterBuffer->SetPSBuffer(0);
	_quad->Render();
}
