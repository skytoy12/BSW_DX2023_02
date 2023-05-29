#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	~DungreedScene();
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
private:
	shared_ptr<class Dungreed> _dungreedPlayer;
	shared_ptr<class DungreedBoss> _boss;

};

