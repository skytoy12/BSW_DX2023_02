#pragma once
class RushMonster : public Monster
{
public :
	enum State_RushMonster
	{
		IDLE,
		WALK,
		RUSHREADY,
		RUSH,
		RUSHEND,
		TURN,
		AIRDEATH,
		DEATH,
		DEATHEND
	};
	RushMonster();
	~RushMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	void AllStop();

	void SetState(State_RushMonster type);
	void SetAndResetState(State_RushMonster type);
	void SetAndPlayState(State_RushMonster type);

	void TotalUpdate(State_RushMonster type);

	void DeathStart();

	void Turn();

	void UnActiveIdle();
	void Active();
	void RightLeft();
	void WalkChange();

	void RushEvent();
	void RushFinish();
	void TurnEvent();
	void DeathEvent();

	void SetPlayer(shared_ptr<Player> target) { _targetPlayer = target; }

	shared_ptr<Collider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private :
	void SetLeft();
	void SetRight();

	State_RushMonster _curstate = IDLE;
	State_RushMonster _oldstate = IDLE;


	float _attackCoolTime = 0.0f;
	float _turnCoolTime = 2.0f;
	float _rushTime = 0.0f;
	bool _isRush = false;
	bool _isTurn = false;
	bool _isDeath = false;
};

