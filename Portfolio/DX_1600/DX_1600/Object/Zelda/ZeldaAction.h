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

	void GetPotion(shared_ptr<class ZeldaPotion> other);

	int GetHp() { return _hp; }

	void Recovery(int value) { _hp += value; }

	void Select();

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

	void CreateAction();
	void CreateRun(float h, float w, int Y, string name, shared_ptr<SRV> srv, Action::Type type);
	void CreateIdle(float h, float w, int Y, string name, shared_ptr<SRV> srv, Action::Type type, int num);

	void EndEvent() { _isEnd = true; }

private :
	bool _isEnd = false;

	int _hp = 10;

	State _state = State::NONE;

	shared_ptr<Sprite> _sprite;
	shared_ptr<RectCollider> _collider;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Transform> _transform;

	shared_ptr<class ZeldaPotion> _potion1;
	shared_ptr<class ZeldaPotion> _potion2;
	shared_ptr<class ZeldaPotion> _potion3;
	shared_ptr<class ZeldaPotion> _potion4;
};

