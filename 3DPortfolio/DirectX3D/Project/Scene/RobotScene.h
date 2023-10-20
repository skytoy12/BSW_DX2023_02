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


private:
	Robot* robot;
};

