#pragma once
class Sky
{
public:
	Sky();
	~Sky();

	void Render();
	void PostRener();

private:
	Sphere* sphere;

	RasterizerState* rs;

	SkyBuffer* buffer;
};

