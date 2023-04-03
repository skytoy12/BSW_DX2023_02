#pragma once
class Scene
{
public :
	Scene() {}
	virtual ~Scene();

	virtual void Updata() abstract;
	virtual void Render(HDC hdc) abstract;


protected :
};

