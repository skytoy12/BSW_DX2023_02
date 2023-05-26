#pragma once
class Dun_Bullet
{
public :
	Dun_Bullet();
	~Dun_Bullet();

	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);

	Vector2 GetPos() { return _quad->GetTransform()->GetPos(); }

	bool _isActive = false;

private :
	shared_ptr<Quad> _quad;

	Vector2 _dir = Vector2();
	float _speed = 200.0f;
};
