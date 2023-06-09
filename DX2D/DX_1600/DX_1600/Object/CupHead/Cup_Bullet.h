#pragma once
class Cup_Bullet
{
public :
	enum Bullet_State
	{
		INTRO,
		LOOP,
		NONE
	};

	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void SetAngle(float value) { _collider->GetTransform()->SetAngle(value); }

	shared_ptr<CircleCollider> GetCollider() { return _collider; }


	void EndEvent();

	bool _isActive = false;
private :
	Bullet_State _state = Bullet_State::LOOP;


	Vector2 _dir = Vector2(0, 0);
	float _speed = 200.0f;

	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider>_collider;

	vector<shared_ptr<Action>> _actions;


	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;
};

