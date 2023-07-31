#pragma once
class Boss : public Monster
{
public :
	enum State_Boss
	{
		IDLE
	};
	Boss();
	~Boss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;


	void SetTarget(shared_ptr<Transform> target) { _target = target; }

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private :
	void SetLeft();
	void SetRight();
	shared_ptr<CircleCollider> _col;
	shared_ptr<CircleCollider> _landPoint;
	State_Boss _curstate = IDLE;
	State_Boss _oldstate = IDLE;

	float _attackCoolTime = 0.0f;

	float _jumpTime = 0.0f;
	bool _isJump = false;
	bool _isAttack = false;
	bool _isturn = false;

};

