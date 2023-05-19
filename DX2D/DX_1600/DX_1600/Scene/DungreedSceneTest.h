#pragma once
class DungreedSceneTest : public Scene
{
public :
	DungreedSceneTest();
	~DungreedSceneTest();
	virtual void Update() override;

	virtual void Render() override;
private :
	shared_ptr<class Dun_Player> _dun_player;

};

