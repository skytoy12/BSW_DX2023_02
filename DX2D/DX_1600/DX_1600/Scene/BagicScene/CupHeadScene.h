#pragma once
class CupHeadScene : public Scene
{
public :
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();
private :
	shared_ptr<class Cup_Player> _player;
	shared_ptr<class Cup_Boss> _boss;
	shared_ptr<class Cup_Track> _track;
	shared_ptr<class Cup_Track2> _track2;
	shared_ptr<class Cup_Wall> _wall;
	shared_ptr<class Cup_Boss_2phase> _2phase;
};

