#include "framework.h"
#include "Program.h"

#include "../Scenes/PaintScene.h"

Program::Program()
{
	_curScene = make_shared<PaintScene>();
}

Program::~Program()
{
}

void Program::Updata()
{
	_curScene->Updata();
}

void Program::Render(HDC hdc)
{
	_curScene->Render(hdc);
}
