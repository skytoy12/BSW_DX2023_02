#pragma once
class Effect
{
public :
	Effect(string name, wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.03f, Action::Type type = Action::Type::END);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 pos);
	void End();
	void SetLeft();
	void SetRight();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	void SetScale(Vector2 scale) { _transform->SetScale(scale); }
	void SetAngle(float angle) { _transform->SetAngle(RADIAN(angle)); }

	bool _isActive = false;

private :
	void CreateAction(string name, wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.1f, Action::Type type = Action::Type::END);

	shared_ptr<Transform> _transform;
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

