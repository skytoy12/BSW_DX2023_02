#pragma once
class Dungreed
{
public :
	Dungreed();
	~Dungreed();

	void Update();
	void Render();

	void SetBowAngle();

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }

	void SetPratent(shared_ptr<Transform> parent) { _quad->GetTransform()->SetParent(parent);}

	void Move(Vector2 movePos) { _quad->GetTransform()->AddVector2(movePos); }

	const Vector2& GetPos() { return _quad->GetTransform()->GetPos(); }

	vector<shared_ptr<class DungreedBullet>> GetBullets() { return _bullets; }


	void Fire();

private :
	shared_ptr<Quad> _quad;

	shared_ptr<Transform> _bowSlot;
	shared_ptr<Quad> _bow;

	vector<shared_ptr<class DungreedBullet>> _bullets;


};

