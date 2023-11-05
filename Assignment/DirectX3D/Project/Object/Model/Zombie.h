#pragma once
class Zombie : public ModelAnimator
{
public:
	Zombie(string name);
	~Zombie();


	void Update();
	void Render();
	void Debug();

	void UpdateCollider();

	void SetTarget(Transform* target) { this->target = target; }

	void SetSpeed(float value) { moveSpeed = value; }

	Collider* GetCollider() { return collider; }

	void Hp() { hp -= 1; }
	void hitted(Bullet* bullet);
private :
	void Move();
	void Attack();

private:
	float speed = 1.0f;
	float takeTime = 0.2f;

	int hp = 5;

	Transform* model;

	Collider* collider;

	Vector3 dir;

	Transform* target;

	float moveSpeed = 5.0f;
	float  rotSpeed = 3.0f;

	float hitTime = 0.0f;
};

