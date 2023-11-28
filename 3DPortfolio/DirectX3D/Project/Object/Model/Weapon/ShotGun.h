#pragma once
class ShotGun : public Gun
{
public:
	ShotGun(string file);
	~ShotGun();

	void Update();
	void Render();
	void PostRender();
	void Debug();

	void Fire();
private:
	vector<Bullet*> bullets;
	bool isAttack = false;
	float attackTime = 10.0f;
};



