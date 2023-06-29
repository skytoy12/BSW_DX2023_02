#pragma once
class Cup_Boss_2phase
{
public :
	enum phase_State
	{
		START,
		LOOP
	};

	Cup_Boss_2phase();
	~Cup_Boss_2phase();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	shared_ptr<RectCollider> GetCollider() { return _collider; }

	void Fire(Vector2 targetPos);

	void EndEvent();

	void Damage(int value) { _hp -= value; }

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos * DELTA_TIME); }

	bool _isAlive = false;

	bool _isDead = false;

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

	bool isCollision_Bullets(shared_ptr<Collider> col);

	void SetLeft();
	void SetRight();

private :

	vector<shared_ptr<class Cup_Bullet>> _bullets;

	int _hp = 10;

	float _coolTime = 0.0f;
	float _atkSpeed = 1.0f;

	bool _isLeft = true;

	int _coolDown = 3;

	shared_ptr<IntBuffer> _intBuffer;

	phase_State _state = phase_State::START;

	shared_ptr<RectCollider>_collider;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;
};

