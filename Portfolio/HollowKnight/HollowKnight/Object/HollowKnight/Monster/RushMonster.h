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
		DEATH
	};
	RushMonster();
	~RushMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	void SetState(State_RushMonster type);
	void SetAndResetState(State_RushMonster type);
	void SetAndPlayState(State_RushMonster type);

	void Active();
	void RightLeft();
	void WalkChange();

	void RushEvent();
	void RushFinish();

	void SetTarget(shared_ptr<Transform> target) { _target = target; }

	shared_ptr<RectCollider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private :
	void SetLeft();
	void SetRight();

	State_RushMonster _curstate = IDLE;
	State_RushMonster _oldstate = IDLE;

	shared_ptr<RectCollider> _col;
	float _attackCoolTime = 0.0f;
	float _rushTime = 0.0f;
	bool _isRush = false;
};

