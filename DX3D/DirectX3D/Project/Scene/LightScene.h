#pragma once
class LightScene : public Scene
{
public:
	LightScene();
	~LightScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	Quad* floor;

	Groot* groot;

	Model* bunny;

	Sphere* sphere;
};



