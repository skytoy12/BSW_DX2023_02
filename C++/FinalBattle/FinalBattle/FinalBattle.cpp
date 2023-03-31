#include "framework.h"



bool PlayerAllDead(vector<shared_ptr<Creature>> v)
{
	
	for (auto& player : v)
	{
		if (player->IsAlive() == true)
			return false;
	}
	return true;
}




int main()
{
	SoundManager::Creat();
	srand(unsigned int(time(NULL)));
	shared_ptr<World> world = make_shared<World>();
	
	
	while (true)
	{
		world->Battle();
		if (world->End())
			break;
	}
	
	
	SoundManager::Delete();


	return 0;
}