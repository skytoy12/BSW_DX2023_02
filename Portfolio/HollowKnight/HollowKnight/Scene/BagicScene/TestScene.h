#pragma once
class TestScene : public Scene
{
public :
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private :
	shared_ptr<class Player> _player;
	shared_ptr<class JumpMonster> _mon1;
	shared_ptr<RectCollider> _col;
	float _scale = 0.5f;
};

