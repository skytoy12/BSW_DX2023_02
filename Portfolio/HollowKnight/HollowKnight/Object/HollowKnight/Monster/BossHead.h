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

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive = false;
private :
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	State_BossHead _curstate = IDLE;
};

