#pragma once
class BossTestScene : public Scene
{
public :
	BossTestScene();
	~BossTestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

private :
	shared_ptr<class Player> _player;
	shared_ptr<class Boss> _boss;
	shared_ptr<RectCollider> _col;
	float _scale = 0.75f;


};

