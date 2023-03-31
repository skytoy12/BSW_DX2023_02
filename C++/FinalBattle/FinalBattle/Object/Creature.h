#pragma once
class Creature
{
public :
	Creature(float hp, float atk, string name);
	virtual ~Creature();
	virtual void Damaged(float amount, shared_ptr<Creature> attacker = nullptr);
	virtual void Attack(shared_ptr<Creature> victim)abstract;
	bool IsAlive();
	const float& GetHp() { return _hp; }
	const float& GetAtk() { return _atk; }
	const string& Getname() { return _name; }
	const CreatureType& GetType() { return _type; }
	int RandomNum(int min, int max);
	

protected :
	float _hp;
	float _atk;
	string _name;
	bool _isAlive;
	CreatureType _type;
};

