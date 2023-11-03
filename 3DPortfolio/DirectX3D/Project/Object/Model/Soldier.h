#pragma once
class Soldier : public ModelAnimator
{
public:
	Soldier();
	~Soldier();

	void Update();
	void Render();
	void Debug();
	void PostRender();
private:
	float speed = 1.0f;
	float takeTime = 0.2f;
};



