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

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
private :

};

