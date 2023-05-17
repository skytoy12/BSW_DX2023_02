#include "framework.h"
#include "SolorSystem.h"
#include "../Object/SolarSystem/Planet.h"

SolorSystem::SolorSystem()
{
	_planetSun = make_shared<Planet>(L"Resource/sun.png", Vector2(0.1f, 0.1f), 0.0005);
	_planetEarth = make_shared<Planet>(L"Resource/earth.png", Vector2(0.07f, 0.07f), 0.0005);
	_planetMoon = make_shared<Planet>(L"Resource/moon.png", Vector2(0.05f, 0.05f), 0.0005);

	_planetMoon->SetPratent(_planetEarth->GetRevolution());
	_planetEarth->SetPratent(_planetSun->GetRevolution());
	_planetMoon->setPosition(Vector2(100, 0));
	_planetEarth->setPosition(Vector2(300, 0));
}

SolorSystem::~SolorSystem()
{
}

void SolorSystem::Update()
{
	_planetSun->setPosition(mousePos);

	_planetSun->Update();
	_planetEarth->Update();
	_planetMoon->Update();
}

void SolorSystem::Render()
{
	_planetSun->Render();
	_planetEarth->Render();
	_planetMoon->Render();
}
