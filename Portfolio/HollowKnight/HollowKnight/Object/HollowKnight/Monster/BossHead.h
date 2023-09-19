#pragma once
class BossHead
{
public:
	enum State_BossHead
	{
		IDLE,
		HIT,
		LASTHEAD
	};

	BossHead();
	~BossHead();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void SetRGB(float R, float G, float B);

	void hurt();

	int GetHP() { return _hp; }

	Vector2 GetPos() { return _col->GetPos(); }

	void UnbeatableToIdleH();

	void SetIDLE() { _curstate = IDLE; }

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive = false;
	bool _lastHead = false;
private :
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;


	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	State_BossHead _curstate = IDLE;

	int _hp = 30;
	int _lasthp = 10;



	float _unbeatableTimeH = 0.0f; // 몬스터 피격시 잠시 무적이 되는 시간
	bool _isUnbeatableH = false;

	shared_ptr<MonsterBuffer> _monsterBuffer;
};

