#pragma once
class Soldier : public ModelAnimator
{
public:
	enum SoldierState
	{
		IDLE,
		RUN,
		WALK,
		RIFLEFIRE,
		SHOTGUNFIRE
	};

	enum GunType
	{
		SHOTGUN,
		RIFLE
	};

	Soldier();
	~Soldier();

	void Update();
	void Render();
	void Debug();
	void PostRender();
	void ShotGunUpdate();
	void RifleUpdate();


	void SetAngle(Vector3 dir);
	void Move();
	void SetDestination(Vector3 pos) { destination = pos; }
	void SetBulletDestination(Vector3 pos) { bulletDestination = pos; }
	Vector3 GetDestination() { return destination; }
	
	void SetMoveSpeed(float value) { moveSpeed = value; }


	void UpdateGunPos();

	void SetShotGunIdle(); // 샷건 평소 위치 조정
	void SetShotGunRun();  // 샷건 들고 뛸때 위치 조정
	void SetShotGunFire(); // 샷건 쏠때 위치 조정

	void SetRifleIdle();   // 라이플 평소 위치 조정
	void SetRifleRun();	   // 라이플 들고 뛸때 위치 조정
	void SetRifleFire();   // 라이플 쏠때 위치 조정

	void SetAnim(); // 모델의 동작을 조정
	void SetGunAnim(); // 모델의 총쏘는 동작을 조정

	void AttackTimeZero();

	void ShotGunFire();
	void RifleFire();
	void Delay();

	void SetClip(SoldierState type);

	bool isMove();

	GunType GetGunType() { return curWeapon; }
	SoldierState GetCurState() { return curState; }
private:
	SoldierState curState;
	SoldierState oldState;
	Groot* groot;

	GunType curWeapon = RIFLE;

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
	float attackDelay = 0.0f;
};



