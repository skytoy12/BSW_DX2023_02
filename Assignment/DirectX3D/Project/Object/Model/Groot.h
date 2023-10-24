#pragma once
class Groot : public ModelAnimator
{
	enum AnimState
	{
		IDLE,
		RUN,
		ATTACK
	} curState = IDLE;

public:
	Groot();
	~Groot();

	void Update();
	void Render();
	void Debug();

	void UpdateRightHand();

	void SetClip(AnimState state);
private :
	void Move();
	void Attack();
	void Dir();
private:
	float speed = 1.0f;
	float takeTime = 0.2f;

	Model* weapon;

	Transform* rightHand;

	float moveSpeed = 50.0f;
	float  rotSpeed =  3.0f;

	Vector3 dir;
};

