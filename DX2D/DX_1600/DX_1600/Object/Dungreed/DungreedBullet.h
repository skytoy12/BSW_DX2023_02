#pragma once
class DungreedBullet
{
public :
	DungreedBullet(wstring file, Vector2 scale);
	~DungreedBullet();

	void Update();
	void Render();

	void SetIsActive(bool active) { _isActive = active; }
	bool GetIsActive() { return _isActive; }

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	void AddPosition(Vector2 pos) { _quad->GetTransform()->AddVector2(pos); }
	void SetParentofBullet(shared_ptr<Transform> parent) { _quad->GetTransform()->SetParent(parent); }
private :
	Vector2 _scale;

	shared_ptr<Quad> _quad;

	bool _isActive;

};

