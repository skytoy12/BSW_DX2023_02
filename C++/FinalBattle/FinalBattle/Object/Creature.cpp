#include "framework.h"
#include "Creature.h"

Creature::Creature(float hp, float atk, string name)
	:_hp(hp), _atk(atk), _name(name), _isAlive(true)
{
	_type = CreatureType::NONE;
}

Creature::~Creature()
{
}



int Creature::RandomNum(int min, int max)
{
	return rand() % ((max - min) + 1) + min;
}

void Creature::Damaged(float amount, shared_ptr<Creature> attacker = nullptr)
{
	if (amount <= 0.0f || _isAlive == false)
		return;
	_hp -= amount;

	if (_hp <= 0.0f)
	{
		_hp = 0.0f;
		cout << this->_name << "가(이) 사망하였습니다." << endl;
		_isAlive = false;
	}
}

void Creature::Attack(shared_ptr<Creature> victim)
{
	srand(unsigned int (time(NULL)));
	if (victim == nullptr)
		return;
	if (_isAlive == false || victim->_isAlive == false)
		return;
	cout << this->_name << "가(이) " << victim->_name << "을 공격하였습니다." << endl;
	victim->Damaged(_atk * RandomNum(1,20));
}

bool Creature::IsAlive()
{
	return _isAlive;
}

