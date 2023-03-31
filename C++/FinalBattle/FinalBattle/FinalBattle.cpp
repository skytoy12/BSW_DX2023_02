#include "framework.h"







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