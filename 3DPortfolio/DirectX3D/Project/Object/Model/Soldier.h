#pragma once
class Soldier : public ModelAnimator
{
public:
	enum SoliderState
	{
		IDLE,
		RUN,
		WALK,
		RIFLE,
		SHOTGUN
	};

	Soldier();
	~Soldier();

	void Update();
	void Render();
	void Debug();
	void PostRender();

	void SetAngle(Vector3 dir);
	void Move();
	void SetDestination(Vector3 pos) { destination = pos; }
	void SetBulletDestination(Vector3 pos) { bulletDestination = pos; }
	Vector3 GetDestination() { return destination; }
	
	void SetMoveSpeed(float value) { moveSpeed = value; }

	void UpdateGunPos();
	void SetGunIdle();
	void SetGunRun();

	void GunFire();

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
	Vector3 bulletDestination = { 0, 0, 0 };

	Transform* gunPos;
	Collider* firePoint;
	ShotGun* shotGun;
	Rifle* rifle;

	float rotDamping = 5.0f;

};



