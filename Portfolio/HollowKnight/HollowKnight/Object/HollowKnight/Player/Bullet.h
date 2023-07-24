#pragma once
class Bullet
{
public :
	enum State_Bullet
	{
		IDLE,
		END
	};

	Bullet();
	~Bullet();

	void Update();
	void Render();
	void Shoot(Vector2 startPos, Vector2 dir = { 1,0 });

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void EndEvent();

	void SetState(State_Bullet type);
	void SetAndResetState(State_Bullet type);

	bool _isActive = false;
private :
	bool _isLeft = false;
	Vector2 _dir = { 1,0 };
	float _speed = 800.0f;
	float _length = 0.0f;

	State_Bullet _curstate = IDLE;
	State_Bullet _oldstate = IDLE;

	void SetLeft();
	void SetRight();

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<CircleCollider> _col;
};

