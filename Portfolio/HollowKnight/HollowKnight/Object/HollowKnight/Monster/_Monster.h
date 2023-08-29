#pragma once
class Monster
{
	friend class Player;
public :
	Monster();
	virtual ~Monster() {}
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void Attack() abstract;

	void Gravity(shared_ptr<CircleCollider> col);
	void Gravity(shared_ptr<RectCollider> col);

	void HighGravity(shared_ptr<CircleCollider> col);
	void HighGravity(shared_ptr<RectCollider> col);

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);
protected :
	int _hp = 0;
	float _jumpPower = 0.0f;
	float _speed = 150.0f;
	Vector2 _dir = { 1,0 };

	bool _isAlive = true;
	bool _isActive = false;
	bool _isLeft = false;

	//weak_ptr<Transform> _target;
	weak_ptr<class Player> _targetPlayer;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
};

