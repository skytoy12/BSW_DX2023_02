#include "framework.h"
#include "Boss.h"

Boss::Boss(float hp, float atk, string name)
	: Monster(hp, atk, name)
{
	_type = CreatureType::AGGRO_ABLE;
}

Boss::~Boss()
{
}

void Boss::Attack(shared_ptr<Creature> victim)
{
	srand(unsigned int(time(NULL)));
	if (victim == nullptr)
		return;
	if (_isAlive == false || victim->IsAlive() == false)
		return;
	cout << this->_name << "가(이) " << victim->Getname() << "을 공격하였습니다." << endl;
	cout << this->_name << "가(이)" << victim->Getname() << "에게 " << this->GetAtk() << "만큼 피해를 입혔습니다" << endl;
	SoundManager::GetInstance()->BAsound();
	victim->Damaged(_atk * RandomNum(10, 20), victim);
	
}

void Boss::Damaged(float amount, shared_ptr<Creature> attacker)
{
		Creature::Damaged(amount);
		string name = attacker->Getname();
		auto iter = std::find_if(_aggrotable.begin(), _aggrotable.end(), [name](const AggroInfo& info)->bool
			{
				if (info.Attacker->Getname() == name)
					return true;
				return false;
			});
		if (iter != _aggrotable.end())
		{
			iter->totalDamage += amount;
		}
		else
		{
			AggroInfo info;
			info.Attacker = attacker;
			info.totalDamage = amount;
			_aggrotable.push_back(info);
		}
}


void Boss::AttackPlayersByAggro()
{
	auto iter = std::remove_if(_aggrotable.begin(), _aggrotable.end(),
		[](const AggroInfo& info)-> bool
		{
			if (!info.Attacker->IsAlive())
				return true;
			return false;
		});
	_aggrotable.erase(iter, _aggrotable.end());

	std::sort(_aggrotable.begin(), _aggrotable.end(), [](const AggroInfo& info1, const AggroInfo& info2)-> bool
		{
			if (info1.totalDamage > info2.totalDamage)
				return true;
			return false;
		});

	int count = 0;
	for (auto& info : _aggrotable)
	{
		if (count == _range)
			break;
		Attack(info.Attacker);
		count++;
	}
}

void Boss::Angry()
{
	cout << endl;
	cout << endl;
	cout << _name << "가 분노하였습니다!!!" << endl;
	cout << endl;
	cout << endl;
	_atk *= 2;
}
