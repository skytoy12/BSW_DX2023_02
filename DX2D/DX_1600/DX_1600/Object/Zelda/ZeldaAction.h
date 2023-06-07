#pragma once
class ZeldaAction
{
public :
	ZeldaAction();
	~ZeldaAction();

	void Update();
	void Render();
	void PostRender();

	void Select();

	void CreateAction();

	void EndEvent() { _isEnd = true; }

private :
	bool _isEnd = false;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _forwordAction;
	shared_ptr<Action> _backAction;
	shared_ptr<Action> _rightAction;
	shared_ptr<Action> _leftAction;

	shared_ptr<Action>* _action;
	shared_ptr<Transform> _transform;
};

