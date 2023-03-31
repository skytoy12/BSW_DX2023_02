#include "framework.h"
#include "World.h"

World::World()
{
	_boss = make_shared<Boss>(1000000, 50, "시공의 인도자 우서");
	for (int i = 0; i < 10; i++)
	{
		int random = RandomNum3(1, 3);
		if (random == 1)
		{
			shared_ptr<Creature> player = make_shared<Archer>(RandomNum3(1500, 2500), RandomNum3(1000, 1500), "궁수" + to_string(i + 1));
			_players.push_back(player);
		}
		if (random == 2)
		{
			shared_ptr<Creature> player = make_shared<Knight>(RandomNum3(3500, 4500), RandomNum3(500, 1000), "기사" + to_string(i + 1));
			_players.push_back(player);
		}
		if (random == 3)
		{
			shared_ptr<Creature> player = make_shared<Magician>(RandomNum3(1000, 1500), RandomNum3(250, 300), "마법사" + to_string(i + 1));
			_players.push_back(player);
		}
	}
}

World::~World()
{
}

void World::Battle()
{
	for (auto player : _players)
	{
		player->Attack(_boss);
	}
	cout << "보스의 HP가 " << _boss->GetHp() << "만큼 남았습니다." << endl;


	dynamic_pointer_cast<Boss>(_boss)->AttackPlayersByAggro();
}

bool World::End()
{
	bool PlayerAllDead = true;
	for (auto player : _players)
	{
		if (player->IsAlive() == true)
		{
			PlayerAllDead = false;
			break;
		}
	}
	if (PlayerAllDead == true)
	{
		cout << "전멸하였습니다..." << endl;
		cout << "전투에서 패배하였습니다..." << endl;
	}
	if (_boss->IsAlive() == false)
	{
		cout << "보스를 쓰러뜨렸습니다!!!" << endl;
		cout << "전투에서 승리하였습니다!!!" << endl;
	}

	return PlayerAllDead || (_boss->IsAlive() == false);
}


