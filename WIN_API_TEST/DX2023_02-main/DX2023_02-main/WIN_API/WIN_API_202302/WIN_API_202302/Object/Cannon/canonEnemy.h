#pragma once
class canonEnemy
{
public :
	canonEnemy(Vector2 pos);
	~canonEnemy();

	void Update();
	void Render(HDC hdc);
	void Damaged(shared_ptr<Cannon> other);
	bool IsAlive() { return _isAlive; }
	void Active();
	void NonActive();

private :
	bool _isAlive = false;
	float _muzzleLength = 100.0f;
	float _hp = 1000.0f;
	shared_ptr<CircleCollider> _body;
	shared_ptr<Line> _muzzle;
};

