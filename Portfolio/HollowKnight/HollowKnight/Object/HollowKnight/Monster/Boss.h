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
		GROGYATTACK,
		GROGYSTART,
		GROGYROLLING,
		GROGY,
		GROGYHEAD
	};

	struct WeaponMove
	{
		float _weaponAngle;
		bool _isPositive;
		int _count;
		float _speed;
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

	virtual void Hitted(shared_ptr<Collider> col) override;

	void ShakeEvent();

	void TurnEvent();
	void AttackReadyEvent();
	void AttackEvent();
	void GrogyEvent();

	void SetActionSpeed(State_Boss type, float speed);

	void LandAttackShakeEvent();
	void GrogyAttackShakeEvent();
	void JumpAttackShakeEvent();
	void GrogyEndEvent();
	void GrogyKnockBack();


	int Return();

	void AllStop();

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
	void JustJumpPattern();

	void Grogy();
	void GrogyRollingFinish();

	void SetPlayer(shared_ptr<Player> target) { _targetPlayer = target; _head->BossHead::SetPlayerH(target); }

	shared_ptr<Collider> GetCollider() { return _heatBox; }
	shared_ptr<Collider> GetGravityCollider() { return _col; }

	shared_ptr<BossHead> GetHead() { return _head; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private :
	void SetLeft();
	void SetRight();
	shared_ptr<Collider> _heatBox;
	shared_ptr<Collider> _weaponCol;
	shared_ptr<Collider> _jumpLine;
	shared_ptr<Collider> _landLine;

	shared_ptr<BossHead> _head;

	State_Boss _curstate = IDLE;
	State_Boss _oldstate = IDLE;

	float _chargeTime = 0.0f; // ������ �����غ��ǿ��� ���ݸ�Ǳ��� �����ϴ� �ð�

	float _turnCoolTime = 2.0f; // ������ �ϸ���� ��Ÿ��(������ �¿찡 �ٲ�°��� ���� ���� ��Ÿ��)
	float _attackCoolTime = 0.0f; // ������ ���ϻ��� ����
	float _shakeTiming = 0.0f; // ������ ���Ⱑ ���� ����ġ�� ������ shake ȿ���� �ֱ����� ���� Ÿ�̸�
	float _jumpAttackTime = 0.0f; // ������ ���������� �� �� ���⸦ ����ġ�� ������ �����ϱ� ���� Ÿ�̸�
	float _rollingTime = 0.0f; // ������ �׷α���°� �� �� �󸶳� �������� �����ϱ� ���� Ÿ�̸�
	float _GrogyStopTime = 0.0f; // ������ �����ִ� �ڼ����� �Ӹ��� ���������� ������� �ٲ�� ������ �ð��� �����ϱ� ���� Ÿ�̸�
	float _grogySpeed = 0.0f; // ���� �׷α�� �������� �ӵ�

	int _armor = 30;
	int _hitCount = 0;

	WeaponMove _weaponMove = { -2.29f, true, 0 , 0.0f};

	Vector2 _landPoint = { 0.0f, 0.0f };

	Vector2 _location = { 0,0 };
	float _jumpTime = 0.0f;
	bool _isJump = false;
	bool _isAttack = false;
	bool _isJumpAttack = false;

	bool _isJustJump = false;
	bool _isJumpAndLandAttack = false;
	bool _isJumpAndGrogyAttack = false;

	bool _isGrogyAttack = false;
	bool _isTurn = false;
	bool _isWeaponMove = false;
	bool _isWeaponActive = false;

	bool _isGrogy = false;

	int _oldAttackType = 1;
	int _curAttackType = 0;

	int _isreturn = 0;

};

