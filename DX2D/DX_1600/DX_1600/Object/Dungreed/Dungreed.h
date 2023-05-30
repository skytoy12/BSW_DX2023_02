#pragma once
class Dungreed
{
public :
	Dungreed();
	~Dungreed();

	virtual void Update();
	virtual void Render();

	void SetBowAngle();


	void SetPratent(shared_ptr<Transform> parent) { _quad->GetTransform()->SetParent(parent);}
	
	virtual void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }

	virtual void Move(Vector2 movePos) { _quad->GetTransform()->AddVector2(movePos); }

	virtual const Vector2& GetPos() { return _quad->GetTransform()->GetPos(); }

	vector<shared_ptr<class DungreedBullet>> GetBullets() { return _bullets; }

	bool isCollision_Bullets(shared_ptr<Collider> col);


	void Fire();

protected :
	shared_ptr<Quad> _quad;

	shared_ptr<Transform> _bowSlot;
	shared_ptr<Quad> _bow;

	vector<shared_ptr<class DungreedBullet>> _bullets;


};

