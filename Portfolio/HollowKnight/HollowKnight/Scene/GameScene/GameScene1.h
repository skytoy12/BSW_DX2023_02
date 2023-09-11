#pragma once
class GameScene1 : public Scene
{
public:
	GameScene1();
	~GameScene1();


	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

private:
	shared_ptr<Player> _player;
	//vector<shared_ptr<JumpMonster>>
};


