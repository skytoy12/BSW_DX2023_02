#pragma once
class GameScene3 : public Scene
{
public:
	GameScene3();
	~GameScene3();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

	void CreateMap();

	void MoveCol();

	void DashCut();

	void Save();
	void Load();

	void BrickLoad();

private:
	float _scale = 0.75f;
	int _colNum = 0;

	bool _start = true;
	bool _isOn = true;

	shared_ptr<Player> _player;

	vector<shared_ptr<RushMonster>> _RMons;
	vector<shared_ptr<JumpMonster>> _JMons;
	shared_ptr<FlyMonster> _fly;

	vector<shared_ptr<Wall>> _walls;
	vector<shared_ptr<Stool>> _stools;

	shared_ptr<CircleCollider> _Potal;

	shared_ptr<Stool> _stoolA;
	shared_ptr<Stool> _stoolB;
	shared_ptr<Stool> _stoolC;
	shared_ptr<Stool> _stoolD;

	vector<shared_ptr<BrickImage>> _images;
};


