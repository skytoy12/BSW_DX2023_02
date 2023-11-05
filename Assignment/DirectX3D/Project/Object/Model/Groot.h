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

	vector<Bullet*> GetBullet() { return bullets; }

private :
	void Move();
	void Attack();
private:
	float speed = 1.0f;
	float takeTime = 0.2f;

	vector<Bullet*> bullets;

	Model* weapon;

	Transform* rightHand;

	float moveSpeed = 50.0f;
	float  rotSpeed =  3.0f;
};

