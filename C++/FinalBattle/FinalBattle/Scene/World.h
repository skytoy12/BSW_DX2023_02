#pragma once
class World
{
public :
	int RandomNum3(int min, int max)
	{
		return rand() % ((max - min) + 1) + min;
	}
	World();
	~World();
	void Battle();
	bool End();
	
private :
	shared_ptr<Creature> _boss;
	vector<shared_ptr<Creature>>_players;
};

