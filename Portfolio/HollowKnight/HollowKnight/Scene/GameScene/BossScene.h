#pragma once
class BossScene : public Scene
{
public:
	BossScene();
	~BossScene();

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

	shared_ptr<Player> _player;
	shared_ptr<Boss> _boss;

	shared_ptr<CircleCollider> _startButton;
	bool _startActive = true;
	bool _isEnd = false;
	shared_ptr<RectCollider> _startCollider;
	shared_ptr<RectCollider> _endCollider;

	vector<shared_ptr<Wall>> _walls;

	vector<shared_ptr<BrickImage>> _images;

	shared_ptr<BackGround> _backGround;
	shared_ptr<BackGround> _backGround1;
	shared_ptr<BackGround> _backGround2;
};



