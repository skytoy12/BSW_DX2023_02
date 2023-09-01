#pragma once
class BossHead
{
public:
	enum State_BossHead
	{
		IDLE,
		HIT
	};

	BossHead();
	~BossHead();

	void Update();
	void Render();


	void hurt();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);


	void SetPlayerH(shared_ptr<Player> target) { _targetP = target; }

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive = false;
private :
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider>_col;

	bool _isUnbeatableH = false;

	shared_ptr<MonsterBuffer>_monsterBuffer;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	weak_ptr<Player> _targetP;

	State_BossHead _curstate = IDLE;


	int _hp = 18;
	int hitCount = 0;


};

