#pragma once
class Cup_Boss
{
public :

	enum Boss_State
	{
		START,
		LOOP,
		READY1,
		READY2,
		READY3,
		DASHREADY,
		DASHSTART,
		DASHLOOP,
		DASHSTOP,
		DIE
	};

	Cup_Boss();
	~Cup_Boss();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	shared_ptr<RectCollider> GetCollider() { return _collider; }

	void Dash();

	void EndEventDash();

	void EndEvent();

	void DieEvent();

	void EndEventCrash();

	void Damage(int value) { _hp -= value; }

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos * DELTA_TIME); }

	bool _isAlive = false;

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

	bool _isWallCrash = false;

private :
	void SetLeft();
	void SetRight();
	int _hp = 10;


	bool _isLeft = true;



	int _coolDown = 3;

	shared_ptr<IntBuffer> _intBuffer;

	Boss_State _state = Boss_State::START;

	shared_ptr<RectCollider>_collider;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;
};

