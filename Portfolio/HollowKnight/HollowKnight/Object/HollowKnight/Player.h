#pragma once
class Player
{
public :

	enum State_Player
	{
		IDLE,
		RUN
	};

	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

#pragma region Player Move & Attack
	void Move(Vector2 movePos) { _col->GetTransform()->AddVector2(movePos * DELTA_TIME); }
	void Input();
	void Select();
#pragma endregion

#pragma region Player Get Info
	shared_ptr<Transform> GetTransform() { return _transform; }
#pragma endregion


private :
	void SetLeft();
	void SetRight();

	float _jumpPower = 0.0f;

	State_Player _oldstate = Player::State_Player::IDLE;
	State_Player _curstate = Player::State_Player::IDLE;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<CircleCollider> _col;
};

