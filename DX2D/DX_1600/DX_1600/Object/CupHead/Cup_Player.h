#pragma once
class Cup_Player
{
public :

	enum State
	{
		IDLE,
		RUN,
		NONE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos); }
	void Select();

	void CreateIdleAction();
	void CreateRunAction();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

private :
	State _state = Cup_Player::State::IDLE;

	shared_ptr<CircleCollider>_collider;

	vector<shared_ptr<Action>> _actions;


	shared_ptr<Sprite> _idleSprite;
	shared_ptr<Sprite> _runSprite;

	shared_ptr<Transform> _transform;

	Vector2 _fixedPos;
};

