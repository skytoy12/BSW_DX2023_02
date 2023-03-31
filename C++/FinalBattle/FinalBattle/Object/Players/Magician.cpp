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
		cout << this->_name << "��(��) " << victim->Getname() << "�� �����Ͽ����ϴ�." << endl;
		int Damage = _atk * RandomNum(1, 2);
		cout << this->_name << "��(��)" << victim->Getname() << "���� " << Damage << "��ŭ ���ظ� �������ϴ�" << endl;
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
		cout << this->_name << "��(��) [���̾]�� �����Ͽ����ϴ�." << endl;
		int Damage = RandomNum(7000, 10000);
		cout << this->_name << "��(��)" << victim->Getname() << "���� " << Damage << "��ŭ ���ظ� �������ϴ�" << endl;
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
