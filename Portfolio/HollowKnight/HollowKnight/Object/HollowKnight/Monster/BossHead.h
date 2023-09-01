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

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);
	void SetPlayerH(shared_ptr<Player> target) { _targetP = target; }

	void hurt();

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive = false;
private :
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;

	weak_ptr<class Player> _targetP;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	State_BossHead _curstate = IDLE;

	int _hp = 30;
	float _unbeatableTime = 0.0f; // 몬스터 피격시 잠시 무적이 되는 시간
	bool _isUnbeatable = false;

	shared_ptr<MonsterBuffer> _monsterBuffer;
};

