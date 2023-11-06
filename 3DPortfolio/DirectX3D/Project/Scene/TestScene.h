#pragma once
class TestScene : public Scene
{
public:

	TestScene();
	~TestScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;


private:
	Soldier* soldier;

	Terrain* terrain;

	ModelAnimatorInstancing* model;

	int instanceIndex = 0;
	int clip = 0;

	Vector3 pos;
};



