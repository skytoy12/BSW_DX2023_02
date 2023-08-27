#pragma once
class RobotScene : public Scene
{
public:
	RobotScene();
	~RobotScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void CubeUpdate();
	void CubeSize();
	void CubePosition();
	void CubeAngle();

	void ArmAngle();

	void Idle();
	void smile();
	void upset();

	float Ridan(float value) { return value * XM_PI / 180; }

private:
	Cube* mainCube;

	Cube* head;

	Cube* Lshoulder;
	Cube* Rshoulder;

	Cube* Larm;
	Cube* Rarm;

	Cube* Lpelvis;
	Cube* Rpelvis;

	Cube* Lleg;
	Cube* Rleg;

	Cube* Leye;
	Cube* Reye;

	Cube* mouse1;
	Cube* mouse2;

	Cube* body;

	float swing = 1.0f;


};

