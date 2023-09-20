#pragma once
class MapTool : public Scene
{
public :
	MapTool();
	~MapTool();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

	void CreateMap();

	void MoveCol();

	void DashCut();



private:
	float _scale = 0.75f;
	int _colNum = 0;

	bool _isOn = true;
	bool _load = true;

	shared_ptr<Player> _player;

	vector<shared_ptr<Wall>> _walls;

	shared_ptr<RushMonster> _rMon;

	shared_ptr<CircleCollider> _Potal;

	shared_ptr<VectorBrick> _Vbricks;
};

