#pragma once
class DungreedBossScene : public Scene
{
public :
	DungreedBossScene();
	~DungreedBossScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private :
	shared_ptr<CircleCollider> _bossCollider;
	shared_ptr<CircleCollider> _playerCollider;
	vector<shared_ptr<CircleCollider>> _bulletColliders;
	shared_ptr<RectCollider> _floorCollider;

	shared_ptr<DungreedBoss> _boss;
	shared_ptr<Dun_Player_Advanced> _player;

	float _speed = 50.0f;

};

