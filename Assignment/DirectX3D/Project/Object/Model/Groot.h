#pragma once
class Groot : public ModelAnimator
{
public:

	enum State
	{
		RUN,
		IDLE,
		ATTACK
	};

	Groot();
	~Groot();

	void Update();
	void Render();
	void Debug();

	void UpdateRightHand();

	void EndEvent();

private:
	float speed = 1.0f;
	float takeTime = 0.2f;

	State type = IDLE;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Model* weapon;

	Transform* rightHand;
};

