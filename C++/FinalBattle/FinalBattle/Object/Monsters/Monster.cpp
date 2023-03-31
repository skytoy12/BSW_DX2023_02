#include "framework.h"
#include "Monster.h"

Monster::Monster(float hp, float atk, string name)
	:Creature(hp, atk, name)
{
	_type = CreatureType::MONSTER;
}

Monster::~Monster()
{
}

void Monster::Attack(shared_ptr<Creature> victim)
{
	srand(unsigned int(time(NULL)));
	if (victim == nullptr)
		return;
	if (_isAlive == false || victim->IsAlive() == false)
		return;
	cout << this->_name << "��(��) " << victim->Getname() << "�� �����Ͽ����ϴ�." << endl;
	victim->Damaged(_atk);
	SoundManager::GetInstance()->MAsound();
	
}

void Monster::MonsterAttack(vector<shared_ptr<Creature>> victim, int size)
{
	for (int i = 0; i < size; i++)
	{
		Attack(victim[i]);
	}
}


