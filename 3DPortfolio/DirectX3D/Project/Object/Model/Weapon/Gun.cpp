#include "Framework.h"
#include "Gun.h"

Gun::Gun()
	: Model("shot gun triangulated")
{
}

Gun::~Gun()
{
}

void Gun::Update()
{
	Model::Update();
}

void Gun::Render()
{
	Model::Render();
}

void Gun::Debug()
{
}
