#pragma once
class DungreedBullet
{
public :
	DungreedBullet();
	~DungreedBullet();


	void Collider_Update();

	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);

	shared_ptr<Transform> GetTransform() { return _transform; }

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

	Vector2 GetPos() { return _collider->GetTransform()->GetPos(); }


	bool _isActive = false;

private :

	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _collider;

	Vector2 _dir = Vector2();
	float _speed = 200.0f;
};

