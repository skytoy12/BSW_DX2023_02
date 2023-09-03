#pragma once
class SphereScene : public Scene
{
public :
	SphereScene();
	~SphereScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
private :
	Sphere* sphere;
};

