#include "framework.h"
#include "Magician.h"

Magician::Magician(float hp, float atk, string name)
: Player(hp,atk,name)
{
	_type = CreatureType::PLAYER;
}

Magician::~Magician()
{
}

void Magician::Attack(shared_ptr<Creature> victim)
{
	srand(unsigned int(time(NULL)));
	if (_MagicPoint < 10)
	{
		if (victim == nullptr)
			return;
		if (_isAlive == false || victim->IsAlive() == false)
			return;
		cout << this->_name << "가(이) " << victim->Getname() << "을 공격하였습니다." << endl;
		int Damage = _atk * RandomNum(1, 2);
		cout << this->_name << "가(이)" << victim->Getname() << "에게 " << Damage << "만큼 피해를 입혔습니다" << endl;
		SoundManager::GetInstance()->MGAsound();
		if (victim->GetType() == CreatureType::AGGRO_ABLE)
		{
			victim->Damaged(Damage, shared_from_this());
		}
		else
		{
			victim->Damaged(Damage);
		}
		_MagicPoint += 5;
	}
	else
	{
		if (victim == nullptr)
			return;
		if (_isAlive == false || victim->IsAlive() == false)
			return;
		cout << this->_name << "가(이) [파이어볼]을 시전하였습니다." << endl;
		int Damage = RandomNum(7000, 10000);
		cout << this->_name << "가(이)" << victim->Getname() << "에게 " << Damage << "만큼 피해를 입혔습니다" << endl;
		SoundManager::GetInstance()->FBsound();
		if (victim->GetType() == CreatureType::AGGRO_ABLE)
		{
			victim->Damaged(Damage, shared_from_this());
		}
		else
		{
			victim->Damaged(Damage);
		}
		_MagicPoint -= 10;
	}

	
}
