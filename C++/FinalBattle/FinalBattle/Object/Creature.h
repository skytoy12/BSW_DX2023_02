#pragma once
class Creature
{
public :
	Creature(float hp, float atk, string name);
	virtual ~Creature();
	virtual void Damaged(float amount, shared_ptr<Creature> attacker = nullptr);
	virtual void Attack(shared_ptr<Creature> victim)abstract;
	bool IsAlive();
	const float GetHp() { return _hp; }
	const float GetAtk() { return _atk; }
	const int GetAgr() { return _aggravation; }
	const string& Getname() { return _name; }
	const CreatureType& GetType() { return _type; }
	int RandomNum(int min, int max);
	

protected :
	float _hp;
	float _atk;
	string _name;
	bool _isAlive;
	int _aggravation = 0;
	CreatureType _type;
};

