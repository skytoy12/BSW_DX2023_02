#include "framework.h"
#include "Knight.h"

Knight::Knight(float hp, float atk, string name)
: Player(hp, atk, name)
{
	_type = CreatureType::PLAYER;
}

Knight::~Knight()
{
}

void Knight::Attack(shared_ptr<Creature> victim)
{
	srand(unsigned int(time(NULL)));
	if (_stamina < 10)
	{
		if (victim == nullptr)
			return;
		if (_isAlive == false || victim->IsAlive() == false)
			return;
		cout << this->_name << "가(이) " << victim->Getname() << "을 공격하였습니다." << endl;
		int Damage = _atk * RandomNum(10, 20);
		cout << this->_name << "가(이)" << victim->Getname() << "에게 " << Damage << "만큼 피해를 입혔습니다" << endl;
		SoundManager::GetInstance()->KAsound();
		if (victim->GetType() == CreatureType::AGGRO_ABLE)
		{
			victim->Damaged(Damage, shared_from_this());
		}
		else
		{
			victim->Damaged(Damage);
		}
		
		_stamina += 10;
	}
	
}
