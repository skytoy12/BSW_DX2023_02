#include "Framework.h"
#include "Rifle.h"

Rifle::Rifle(string file)
	:Gun(file)
{
}

Rifle::~Rifle()
{
}

void Rifle::Update()
{
	Gun::Update();
}

void Rifle::Render()
{
	Gun::Render();
}

void Rifle::PostRender()
{
}

void Rifle::Debug()
{
}

void Rifle::Fire()
{
}

void Rifle::SetBulletActive(bool value)
{
}
