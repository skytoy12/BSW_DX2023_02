#pragma once
class ZombieScene : public Scene
{
public:
	ZombieScene();
	~ZombieScene();

	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

	void Attack();

	void CameraAngle();

	float Angle(Vector3 translation1, Vector3 translation2);
private:
	Groot* groot;

	Terrain* terrain;

	Ray ray;

	Collider* test;

	Zombie* zombie1;
	Zombie* zombie2;
	Zombie* zombie3;
};



