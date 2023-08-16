#pragma once
class Boss : public Monster
{
public :
	enum State_Boss
	{
		IDLE,
		TURN,
		ATTACKREADY,
		ATTACK,
		ATTACKFINISH,
		JUMPREADY,
		JUMP,
		JUMPATTACK,
		BACKSTEP,
		JUMPTOIDLE,
		GROGYATTACK
	};

	struct WeaponMove
	{
		float _weaponAngle;
		bool _isPositive;
		int _count;
	};

	Boss();
	~Boss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	float Angle(float angle) { return angle * (PI / 180); }

	void SetState(State_Boss type);
	void SetAndResetState(State_Boss type);
	void SetAndPlayState(State_Boss type);

	void TotalUpdate(State_Boss type);

	void TurnEvent();
	void AttackReadyEvent();
	void AttackEvent();
	void ShakeEvent();
	void WeaponColEvent();

#pragma region Update Function
	void LocationFix(State_Boss type);
	void DirFix();
	void Turn();
	void UnActiveIDle();
	void JumpMove();
	void Down();
	void LandChange();
	void BackStep();
	void JumpToIdle();
	void WeaponcolMove();
#pragma endregion

	void LandAttackPattern();
	void JumpAttackPattern();
	void AfterGroggyPattern();

	void SetTarget(shared_ptr<Transform> target) { _target = target; }

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	shared_ptr<RectCollider> GetGravityCollider() { return _gravityCol; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private :
	void SetLeft();
	void SetRight();
	shared_ptr<CircleCollider> _col;
	shared_ptr<CircleCollider> _weaponCol;
	shared_ptr<RectCollider> _gravityCol;
	shared_ptr<RectCollider> _jumpLine;
	shared_ptr<RectCollider> _landLine;
	State_Boss _curstate = IDLE;
	State_Boss _oldstate = IDLE;

	float _chargeTime = 0.0f;

	float _turnCoolTime = 2.0f;
	float _attackCoolTime = 0.0f;
	float _shakeTiming = 0.0f;
	float _jumpAttackTime = 0.0f;

	WeaponMove _weaponMove = { -2.29f, true, 0 };

	Vector2 _landPoint = { 0.0f, 0.0f };

	Vector2 _location = { 0,0 };
	float _jumpTime = 0.0f;
	bool _isJump = false;
	bool _isAttack = false;
	bool _isGrogyAttack = false;
	bool _isTurn = false;
	bool _isWeaponMove = false;
	bool _isWeaponActive = false;

};

