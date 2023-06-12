#pragma once
class Cup_Boss
{
public :

	enum Boss_State
	{
		START,
		LOOP,
		END,
		NONE
	};

	Cup_Boss();
	~Cup_Boss();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size);

	void EndEvent() { _isEnd = true; }

private :
	void SetLeft();
	void SetRight();

	bool _isEnd = false;

	Boss_State _state = Boss_State::START;

	shared_ptr<CircleCollider>_collider;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;
};

