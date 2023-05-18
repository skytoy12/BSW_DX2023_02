#pragma once
class DungreedScene : public Scene
{
public :
	DungreedScene();
	~DungreedScene();

	virtual void Update() override;
	virtual void Render() override;

private :

	shared_ptr<Dungreed> _player;
	shared_ptr<Dungreed> _bow;
	vector<shared_ptr<Dungreed>> _bullets;
};

