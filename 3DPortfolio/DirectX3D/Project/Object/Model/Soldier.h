#pragma once
class Soldier : public ModelAnimator
{
public:
	enum SoliderState
	{
		IDLE,
		RUN,
		WALK
	};

	Soldier();
	~Soldier();

	void Update();
	void Render();
	void Debug();
	void PostRender();

	void SetAngle();
	void Move();
	void SetDestination(Vector3 pos) { destination = pos; }
	Vector3 GetDestination() { return destination; }

	void SetClip(SoliderState type);

	bool isMove();
private:
	SoliderState curState;
	SoliderState oldState;

	Vector3 curPos;
	Vector3 oldPos;

	float animSpeed = 1.0f;
	float takeTime = 0.2f;

	float moveSpeed = 10.0f;
	Vector3 destination = { 0, 0, 0 };

	float test;
	float test2;
	float rotDamping = 5.0f;
};



