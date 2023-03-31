#include "framework.h"
#include "World.h"

World::World()
{
	_boss = make_shared<Boss>(1000000, 50, "�ð��� �ε��� �켭");
	for (int i = 0; i < 10; i++)
	{
		int random = RandomNum3(1, 3);
		if (random == 1)
		{
			shared_ptr<Creature> player = make_shared<Archer>(RandomNum3(1500, 2500), RandomNum3(1000, 1500), "�ü�" + to_string(i + 1));
			_players.push_back(player);
		}
		if (random == 2)
		{
			shared_ptr<Creature> player = make_shared<Knight>(RandomNum3(3500, 4500), RandomNum3(500, 1000), "���" + to_string(i + 1));
			_players.push_back(player);
		}
		if (random == 3)
		{
			shared_ptr<Creature> player = make_shared<Magician>(RandomNum3(1000, 1500), RandomNum3(250, 300), "������" + to_string(i + 1));
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
	cout << "������ HP�� " << _boss->GetHp() << "��ŭ ���ҽ��ϴ�." << endl;


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
		cout << "�����Ͽ����ϴ�..." << endl;
		cout << "�������� �й��Ͽ����ϴ�..." << endl;
	}
	if (_boss->IsAlive() == false)
	{
		cout << "������ �����߷Ƚ��ϴ�!!!" << endl;
		cout << "�������� �¸��Ͽ����ϴ�!!!" << endl;
	}

	return PlayerAllDead || (_boss->IsAlive() == false);
}


