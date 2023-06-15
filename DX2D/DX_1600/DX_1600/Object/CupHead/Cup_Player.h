#pragma once
class Cup_Player
{
public :

	enum State
	{
		IDLE,
		RUN,
		JUMP,
		CHARGE,
		SHOT,
		NONE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos * DELTA_TIME); }
	void Select();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void Input();

	void Jump();

	void AnimationControl();

	void SetType(State _type) { _curstate = _type; }

	void Fire();

	void SetGrounded() { _isJump = false; }

	shared_ptr<Collider> GetCollider() { return _collider; }

	bool _isJump = false;

	Vector2 GetBulletPos();

	bool isCollision_Bullets(shared_ptr<Collider> col);

private :
	void SetLeft();
	void SetRight();
	State _oldstate = Cup_Player::State::IDLE;
	State _curstate = Cup_Player::State::IDLE;

	shared_ptr<CircleCollider>_collider;

	shared_ptr<CircleCollider>_HandCollider;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<class Cup_Bullet>> _bullets;

	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;

	Vector2 _fixedPos;

	float _jumpPower = 0.0f;
};

