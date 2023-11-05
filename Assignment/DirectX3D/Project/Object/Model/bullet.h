#pragma once
class Bullet : public Transform
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();


	void SetActive(bool value) { isActive = value; }
	void SetDir(Vector3 dir);

	Collider* GetCollider() { return bullet; }

	bool isActive = false;

	void Shoot(Vector3 pos);
private:
	Collider* bullet;


	float bulletSpeed = 500.0f;

	Vector3 bulletDir;
};


