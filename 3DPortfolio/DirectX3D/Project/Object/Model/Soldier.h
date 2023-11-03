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

	void Move();
	void SetDestination(Vector3 pos) { destination = pos; }
private:
	float animSpeed = 1.0f;
	float takeTime = 0.2f;

	float moveSpeed = 10.0f;
	Vector3 destination = { 0, 0, 0 };
};



