#pragma once
class SoulOrb
{
public:
	SoulOrb();
	~SoulOrb();

	void Update();
	void PostRender();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	void SetScale(Vector2 scale) { _transform->SetScale(scale); }

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	shared_ptr<Transform> _transform;
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};


