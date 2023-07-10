#pragma once
class Monster
{
public :
	Monster();
	virtual ~Monster() {}
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void Attack() abstract;

	void Gravity();
	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);
protected :
	int _hp = 0;
	bool _isActive = true;
	float _jumpPower = 0.0f;
	float _speed = 1.0f;

	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

};

