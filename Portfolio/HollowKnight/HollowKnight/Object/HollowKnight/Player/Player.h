#pragma once
class Player
{
public :
	friend class Monster;
	enum State_Player
	{
		IDLE,
		RUNSTART,
		RUNNING,
		DASH,
		SLASH,
		CHARGE,
		RECOIL,
		DEATH
	};

	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void SetEnemy(shared_ptr<class Monster> enemy);

	void AllStop();

	void Hitted();
	void HitKnockBack();
	void UnbeatableToIdle();

#pragma region Player Move & Attack
	void Move(Vector2 movePos) { _col->GetTransform()->AddVector2(movePos * DELTA_TIME * _speed); }
	void Select();
	void CoolTime();

	void LeftRight();
	void Jump();
	void Walk();
	void Dash();
	void Attack();
	void ChargeAndFire();
	void ActiveOn(bool value);
	void Gravity();
#pragma endregion

#pragma region EVENT
	void EndEvent();
#pragma endregion 

#pragma region Player Get Info
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<RectCollider> GetWeaponcol() { return _weaponCol; }
	shared_ptr<CircleCollider> GetBulletcol() { return _bulletCol; }
	bool GetIsAttack() { return _isAttack; }
	bool GetWeaponActive() { return _isWeaponActive; }
	bool GetBulletActive() { return _isBulletActive; }
#pragma endregion

#pragma region Player Set Info
	void SetSpeed(float value) { _speed = value; }
	void SetIsJump(bool value) { _isJump = value; }
	void SetState(State_Player type);
	void SetAndResetState(State_Player type);
	void SetWeaponActive(bool value) { _isWeaponActive = value; }
	void SetBulletActive(bool value) { _isBulletActive = value; }
	void SetKBdir(Vector2 value) { _KBdir = value; }
#pragma endregion

	bool _isWeaponActiveB = false;
	bool _isWeaponActiveF = false;
	bool _isWeaponActiveJ = false;
	bool _isWeaponActiveR = false;

private :
	void SetLeft();
	void SetRight();

	float _jumpPower = 0.0f;
	float _speed = 1.0f;
	float _chargeTime = 0.0f;
	float _bulletCoolTime = 10.0f;

	float _unbeatableTime = 0.0f;

	Vector2 _KBdir = { 1,0 };
	float _KBspeed = 150.0f;
	
#pragma region STATE
	bool _isAlive = true;
	bool _isDeath = false;
	bool _isLeft = false;
	bool _isJump = false;
	bool _isAttack = false;

	bool _isWeaponActive = false;
	bool _isBulletActive = false;

	bool _isUnbeatable = false;

	bool _isDash = false;
	bool _isChargeAndFire = false;
#pragma endregion

#pragma region INFO
	int _maxHp = 5;
	int _hp = 5;
#pragma endregion

	State_Player _oldstate = Player::State_Player::IDLE;
	State_Player _curstate = Player::State_Player::IDLE;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _weaponCol;
	shared_ptr<CircleCollider> _bulletCol;
	shared_ptr<CircleCollider> _dashCol;

	vector<weak_ptr<class Monster>> _enemies;

	shared_ptr<class Bullet> _bullet;
	shared_ptr<class ChargeEffect> _effect;
};

