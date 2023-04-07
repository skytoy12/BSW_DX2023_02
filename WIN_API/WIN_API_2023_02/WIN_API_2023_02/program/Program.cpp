#include "framework.h"
#include "Program.h"

#include "../Scenes/PaintScene.h"
#include "../Scenes/LineScene.h"
#include "../Scenes/LineCollisionScene.h"
#include "../Scenes/CanonScene.h"

Program::Program()
{
	_curScene = make_shared<CanonScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	_curScene->Render(hdc);
}
