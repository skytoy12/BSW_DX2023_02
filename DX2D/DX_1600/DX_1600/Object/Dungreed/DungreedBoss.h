#pragma once
class DungreedBoss
{
public :
	DungreedBoss();
	~DungreedBoss();

	void Collider_Update();
	void Update();
	void Render();

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void SetIsActive(bool isActive) { _isActive = isActive; }
	bool _isActive = true;

	int GetHP() { return _hp; }
	void SetHP(int hp) { _hp = hp; }
	void ReduceHP(int damage);

	const Vector2& GetPos() { return _transform->GetPos(); }
private :
	shared_ptr<CircleCollider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	int _hp = 10;

};

