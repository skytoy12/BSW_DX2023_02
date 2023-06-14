#pragma once
class Cup_Boss
{
public :

	enum Boss_State
	{
		START,
		LOOP,
		END,
		DIE,
		NONE
	};

	Cup_Boss();
	~Cup_Boss();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

	void EndEvent();

	void DieEvent();

	void Damage(int value) { _hp -= value; }

	bool _isAlive = true;

private :
	void SetLeft();
	void SetRight();
	int _hp = 10;

	Boss_State _state = Boss_State::START;

	shared_ptr<CircleCollider>_collider;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;
};

