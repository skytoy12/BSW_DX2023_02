#include "framework.h"
#include "BrickImage.h"

BrickImage::BrickImage(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
}

BrickImage::~BrickImage()
{
}

void BrickImage::Update()
{
	if (_isActive == false)
		return;

	_transform->Update();
}

void BrickImage::Render()
{
	if (_isActive == false)
		return;

	_transform->SetBuffer(0);
	_quad->Render();
}


