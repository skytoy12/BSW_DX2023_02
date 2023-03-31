#include "framework.h"
#include "Archer.h"


Archer::Archer(float hp, float atk, string name)
: Player(hp, atk, name)
{
}

Archer::~Archer()
{
}

void Archer::Attack(shared_ptr<Creature> victim)
{
	if (this->_concentration < 10)
	{
		if (victim == nullptr)
			return;
		if (_isAlive == false || victim->IsAlive() == false)
			return;
		cout << this->_name << "가(이) " << victim->Getname() << "을 공격하였습니다." << endl;
		int Damage = _atk * RandomNum(10, 20);
		cout << this->_name << "가(이)" << victim->Getname() << "에게 " << Damage << "만큼 피해를 입혔습니다" << endl;
		SoundManager::GetInstance()->AAsound();
		if (victim->GetType() == CreatureType::AGGRO_ABLE)
		{
			victim->Damaged(Damage, shared_from_this());
		}
		else
		{
			victim->Damaged(Damage);
		}
		
		_concentration += 5;
		
	}
	else
	{
		if (victim == nullptr)
			return;
		if (_isAlive == false || victim->IsAlive() == false)
			return;
		cout << this->_name << "가(이) [더블 샷]을 발동하였습니다." << endl;
		int Damage = _atk * RandomNum(10, 20);
		cout << this->_name << "가(이)" << victim->Getname() << "에게 " << Damage << "만큼 피해를 입혔습니다" << endl;
		cout << this->_name << "가(이)" << victim->Getname() << "에게 " << Damage << "만큼 피해를 입혔습니다" << endl;
		SoundManager::GetInstance()->AAsound();
		victim->Damaged(Damage);
		victim->Damaged(Damage);
		
		_concentration -= 10;

	}
	
}
