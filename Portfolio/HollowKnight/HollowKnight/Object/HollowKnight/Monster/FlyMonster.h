#pragma once
class FlyMonster : public Monster
{
public :
	enum State_FlyMonster
	{
		IDLE,
		AIRDEATH,
		LANDDEATH
	};
	FlyMonster(Vector2 pos);
	~FlyMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	void SetPlayer(shared_ptr<Player> target) { _targetPlayer = target; }

	shared_ptr<Collider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }


	void DeathStart();
	void DeathEvent();

#pragma region Update Function
	void RightLeft();
	void CreateRangePoint();
	void UnActive();
	void Active();
	void SpeedAverage();
	void CreateRandomPos();
#pragma endregion

private :
	void SetLeft();
	void SetRight();
	shared_ptr<Collider> _rangePoint;
	State_FlyMonster _curstate = IDLE;
	State_FlyMonster _oldstate = IDLE;
	Vector2 _originPos = { 0,0 };
	Vector2 _randomPos = { 1,0 };
	float _searchRange = 0.0f;
	float _SRCoolTime = 0.0f;
	float _turnCoolTime = 0.0f;

	float _deathTime = 0.0f;

	bool _isDeath = false;
};

