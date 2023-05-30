#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	~DungreedScene();

	virtual void Collider_Update() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	shared_ptr<class DungreedBoss> _boss;
	shared_ptr<class Dun_Player_Advanced> _dungreedPlayer;
	shared_ptr<RectCollider> _floor;

};

