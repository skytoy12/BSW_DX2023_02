#pragma once
class DungreedBoss
{
public :
	DungreedBoss();
	~DungreedBoss();

	void Update();
	void Render();


	void SetIsActive(bool isActive) { _isActive = isActive; }
	bool _isActive = true;

	int GetHP() { return _hp; }
	void SetHP(int hp) { _hp = hp; }
	void ReduceHP(int damage);

	const Vector2& GetPos() { return _quad->GetTransform()->GetPos(); }
private :
	shared_ptr<Quad> _quad;

	int _hp = 10000;

};

