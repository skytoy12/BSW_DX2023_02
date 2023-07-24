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
		DEATH
	};


	JumpMonster();
	virtual ~JumpMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	void SetState(State_JumpMonster type);
	void SetAndResetState(State_JumpMonster type);
	void SetAndPlayState(State_JumpMonster type);

	void Turn();

	void TurnEvent();
	void JumpEvent();

	void SetTarget(shared_ptr<Transform> target) { _target = target; }

	shared_ptr<RectCollider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
private :
	void SetLeft();
	void SetRight();
	shared_ptr<RectCollider> _col;
	State_JumpMonster _curstate = IDLE;
	State_JumpMonster _oldstate = IDLE;

	float _jumpTime = 0.0f;
	bool _isJump = false;
	bool _isAttack = false;
	bool _isturn = false;
};

