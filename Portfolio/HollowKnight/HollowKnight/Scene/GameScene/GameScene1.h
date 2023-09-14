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

	void CreateMap();

	void MoveCol();

private:
	float _scale = 0.75f;
	int _colNum = 0;

	shared_ptr<Player> _player;

	vector<shared_ptr<Wall>> _walls;

	//vector<shared_ptr<RectCollider>> _cols;

	//shared_ptr<Player> _player;
	//vector<shared_ptr<JumpMonster>>
};


