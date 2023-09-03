#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(Vector4 color, float radius)
{
	for (int i = 0; i < 2160; i++)
	{
		Circle* circle = new Circle(color, radius);
		circles.push_back(circle);
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
}

void Sphere::Render()
{
	for (Circle* circle : circles)
		circle->Render();
}
