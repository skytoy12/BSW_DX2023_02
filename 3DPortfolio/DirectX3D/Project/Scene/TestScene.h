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

	TerrainEditor* terrain;

	ModelAnimatorInstancing* model;

	int instanceIndex = 0;
	int clip = 0;

	bool isFree = false;

	Vector3 pos;
};



