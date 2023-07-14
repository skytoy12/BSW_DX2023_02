#pragma once
class JumpMonster : public Monster
{
public :
	JumpMonster();
	virtual ~JumpMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

	void SetTarget(shared_ptr<Transform> target) { _target = target; }

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
private :

	float _jumpTime = 0.0f;
	bool _isJump = false;
};

