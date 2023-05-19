#pragma once
class Dungreed
{
public :
	Dungreed(wstring file, Vector2 scale);
	Dungreed(wstring file, Vector2 scale, int number, Vector2 bulletScale);
	~Dungreed();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	void SetAngle(float angle) { _quad->GetTransform()->SetAngle(angle); }
	void SetbowAngle(float bowAngle) { _bow->SetAngle(bowAngle); }
	void AddAngle(float angle) { _quad->GetTransform()->AddAngle(angle); }
	void AddPos(Vector2 pos) { _quad->GetTransform()->AddVector2(pos); }
	void SetParent(shared_ptr<Transform> parent) { _quad->GetTransform()->SetParent(parent); _bow->SetParent(parent);
	if (_isWeapon == true)
	{
		for (auto bullet : _bullets)
		{
			bullet->SetParentofBullet(parent);
		}
	}
	}

	vector<shared_ptr<DungreedBullet>> GetBullets() { return _bullets; }

	void fire();

	Vector2 GetPos() { return _quad->GetTransform()->GetPos(); }


	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	shared_ptr<Transform> GetBow() { return _bow; }

private :
	Vector2 _scale;

	shared_ptr<Quad> _quad;

	shared_ptr<Transform> _bow;

	vector<shared_ptr<DungreedBullet>> _bullets;

	Vector2 _bulletScale;

	bool _isWeapon;


};

