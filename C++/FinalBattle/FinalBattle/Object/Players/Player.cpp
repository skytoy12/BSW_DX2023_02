#include "framework.h"
#include "Player.h"

Player::Player(float hp, float atk, string name)
	:Creature(hp, atk, name)
{
	_type = CreatureType::PLAYER;
}

Player::~Player()
{
}



void Player::Attack(shared_ptr<Creature> victim)
{
	srand(unsigned int(time(NULL)));
	if (victim == nullptr)
		return;
	if (_isAlive == false || victim->IsAlive() == false)
		return;
	cout << this->_name << "가(이) " << victim->Getname() << "을 공격하였습니다." << endl;
	victim->Damaged(_atk * RandomNum(1, 20));
	SoundManager::GetInstance()->PAsound();
	_aggravation += _atk;
}








