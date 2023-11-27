#pragma once
class ShotGun : public Gun
{
public:
	ShotGun(string file);
	~ShotGun();

private:
	//vector<Bullet*> bullets;
	bool isAttack = false;
};



