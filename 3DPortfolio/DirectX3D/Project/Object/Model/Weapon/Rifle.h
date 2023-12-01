#pragma once
class Rifle : public Gun
{
public:
	Rifle(string file);
	~Rifle();

	void Update();
	void Render();
	void PostRender();
	void Debug();

	void Fire();

	void SetOrigin(Vector3 pos) { origin = pos; }
	void SetDir(Vector3 pos) { dir = pos; }
	void SetIsAttack(bool value) { isAttack = value; }
	void SetBulletActive(bool value);
	void SetIsAttackTime(float value) { attackTime = value; }

	bool GetIsAttack() { return isAttack; }
	void BulletNumPlus();

private:
	vector<class Bullet*> bullets;
	bool isAttack = false;
	float attackTime = 0.0f;
	Vector3 origin = Vector3(0, 0, 0);
	Vector3 dir = Vector3(0, 0, 0);
	UINT curBulletNum = 0;
	UINT bulletNum = 0;
};


