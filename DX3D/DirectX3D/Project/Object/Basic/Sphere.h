#pragma once
class Sphere
{
public :
	Sphere(Vector4 color, float radius);
	~Sphere();

	void Update();
	void Render();

	float Ridan(float value) { return value * XM_PI / 180; }

private :
	vector<Circle*> circles;
};

