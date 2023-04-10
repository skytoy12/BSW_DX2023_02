#include "framework.h"
#include "CanonScene.h"

CanonScene::CanonScene()
{
	_canon = make_shared<Canon>(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
}

CanonScene::~CanonScene()
{
}

void CanonScene::Update()
{
	_canon->Update();
}

void CanonScene::Render(HDC hdc)
{
	_canon->Render(hdc);
}
