#pragma once
class Robot
{
public :
	enum Part
	{
		MAIN,
		HEAD,
		LSHOULDER,
		RSHOULDER,
		LARM,
		RARM,
		LPELVIS,
		RPELVIS,
		LLEG,
		RLEG,
		LEYE,
		REYE,
		MOUSE1,
		MOUSE2,
		BODY
	};

	Robot();
	~Robot();

	void Update();
	void Render();

	void CreateRobot();

	void CubeUpdate();
	void CubeSize();
	void CubePosition();
	void CubeAngle();


	float Ridan(float value) { return value * XM_PI / 180; }
private :
	vector<Cube*> cubes;
	float swing = 1.0f;
};

