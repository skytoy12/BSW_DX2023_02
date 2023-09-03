#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(Vector4 color, float radius)
{
	for (int i = 0; i < 2160; i++)
	{
		Circle* circle = new Circle(color, radius);
		circles.push_back(circle);
		if (i > 0)
			circles[i]->SetParent(circles[0]);
	}


	for (int i = 0; i < 720; i++)
	{
		circles[i]->rotation.x = Ridan(0.5f * i);
	}

	for (int i = 720; i < 1440; i++)
	{
		circles[i]->rotation.y = Ridan(0.5f * i);
	}

	for (int i = 1440; i < 2160; i++)
	{
		circles[i]->rotation.y = Ridan(90);
		circles[i]->rotation.z = Ridan(0.5f * i);
	}
}

Sphere::~Sphere()
{
}

void Sphere::Update()
{
	for (Circle* circle : circles)
		circle->Update();

	if (KEY_PRESS('Q'))
	{
		circles[0]->rotation.y -= Time::Delta();
	}

	if (KEY_PRESS('E'))
	{
		circles[0]->rotation.y += Time::Delta();
	}

	if (KEY_PRESS('W'))
	{
		circles[0]->rotation.x += Time::Delta();
	}

	if (KEY_PRESS('S'))
	{
		circles[0]->rotation.x -= Time::Delta();
	}

}

void Sphere::Render()
{
	for (Circle* circle : circles)
		circle->Render();
}
