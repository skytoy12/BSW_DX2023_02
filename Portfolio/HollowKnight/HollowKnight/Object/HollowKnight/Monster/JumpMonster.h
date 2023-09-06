#pragma once
class JumpMonster : public Monster
{
public :

	enum State_JumpMonster
	{
		IDLE,
		WALK,
		TURN,
		JUMPREADY,
		JUMP,
		DOWN,
		LAND,
		DEATH,
		DEATHEND
	};


	JumpMonster();
	virtual ~JumpMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	virtual void Hitted(shared_ptr<Collider> col) override;
	virtual void UnbeatableToIdle() override;

	void SetState(State_JumpMonster type);
	void SetAndResetState(State_JumpMonster type);
	void SetAndPlayState(State_JumpMonster type);

	void TotalUpdate(State_JumpMonster type);

	void LocationFix(State_JumpMonster type);

	void AllStop();

	void DeathStart();

	void Turn();

	void TurnEvent();
	void JumpEvent();
	void LandEvent();
	void DeathEvent();

#pragma region Update Function
	void UnActiveIDle();
	void LandMotionChange();
	void Active();
	void AttackStart();
	void JumpMove();
	void DirFix();
	void WalkChange();
#pragma endregion

	void SetPlayer(shared_ptr<Player> target) { _targetPlayer = target; }

	shared_ptr<Collider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
private :
	void SetLeft();
	void SetRight();

	shared_ptr<Collider> _landPoint;
	State_JumpMonster _curstate = IDLE;
	State_JumpMonster _oldstate = IDLE;

	float _attackCoolTime = 0.0f;
	float _turnCoolTime = 2.0f;

	float _jumpTime = 0.0f;
	bool _isJump = false;
	bool _isAttack = false;
	bool _isturn = false;
	bool _isDeath = false;
};

