#pragma once
class Dungreed
{
public :
	Dungreed();
	~Dungreed();

	virtual void Update() abstract;
	virtual void Render();

	void SetBowAngle();


	void SetPratent(shared_ptr<Transform> parent) { _transform->SetParent(parent);}
	
	virtual void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

	virtual void Move(Vector2 movePos) { _transform->AddVector2(movePos); }

	virtual const Vector2& GetPos() { return _transform->GetPos(); }

	vector<shared_ptr<class DungreedBullet>> GetBullets() { return _bullets; }

	bool isCollision_Bullets(shared_ptr<Collider> col);


	void Fire();

protected :
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _bowSlot;

	shared_ptr<Quad> _bow;
	shared_ptr<Transform> _bowTrans;

	vector<shared_ptr<class DungreedBullet>> _bullets;


};

