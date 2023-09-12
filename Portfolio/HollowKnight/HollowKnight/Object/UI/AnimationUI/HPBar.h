#pragma once
class HPBar
{
public:
	enum HPState
	{
		FULL,
		BROKEN,
		NONE
	};

	HPBar();
	~HPBar();

	void Update();
	void PostRender();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	void SetScale(Vector2 scale) { _transform->SetScale(scale); }

private:
	HPState _curstate = FULL;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
};

