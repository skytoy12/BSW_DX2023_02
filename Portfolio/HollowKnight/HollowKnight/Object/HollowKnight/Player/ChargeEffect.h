#pragma once
class ChargeEffect
{
public :
	enum State_Charge
	{
		START,
		END
	};

	ChargeEffect();
	~ChargeEffect();

	void Update();
	void Render();
	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool _isActive = false;

private :
	State_Charge _state = START;
	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
};

