#pragma once
class DungreedBullet
{
public :
	DungreedBullet();
	~DungreedBullet();

	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	Vector2 GetPos() { return _quad->GetTransform()->GetPos(); }


	bool _isActive = false;

private :
	shared_ptr<Quad> _quad;

	Vector2 _dir = Vector2();
	float _speed = 200.0f;
};

