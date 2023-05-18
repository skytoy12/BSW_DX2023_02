#pragma once
class Dungreed
{
public :
	Dungreed(wstring file, Vector2 scale);
	~Dungreed();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	void SetAngle(float angle) { _quad->GetTransform()->SetAngle(angle); }
	void SetbowAngle(float bowAngle) { _bow->SetAngle(bowAngle); }
	void AddAngle(float angle) { _quad->GetTransform()->AddAngle(angle); }
	void SetParent(shared_ptr<Transform> parent) { _quad->GetTransform()->SetParent(parent); _bow->SetParent(parent); }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	shared_ptr<Transform> GetBow() { return _bow; }

private :
	Vector2 _scale;

	shared_ptr<Quad> _quad;

	shared_ptr<Transform> _bow;




};

