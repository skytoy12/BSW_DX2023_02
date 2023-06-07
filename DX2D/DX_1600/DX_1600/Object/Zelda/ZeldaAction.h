#pragma once
class ZeldaAction
{
public :
	enum State
	{
		IDLE_F,
		IDLE_B,
		IDLE_R,
		IDLE_L,
		RUN_F,
		RUN_B,
		RUN_R,
		RUN_L,
		NONE
	};
	ZeldaAction();
	~ZeldaAction();

	void Collider_Update();
	void Update();
	void Render();
	void PostRender();

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos); }


	void Select();

	void CreateAction();

	void EndEvent() { _isEnd = true; }

private :
	bool _isEnd = false;

	State _state = State::NONE;

	shared_ptr<Sprite> _sprite;
	shared_ptr<RectCollider> _collider;

	shared_ptr<Action> _forwordAction;
	shared_ptr<Action> _backAction;
	shared_ptr<Action> _rightAction;
	shared_ptr<Action> _leftAction;

	shared_ptr<Action>* _action;
	shared_ptr<Transform> _transform;
};

