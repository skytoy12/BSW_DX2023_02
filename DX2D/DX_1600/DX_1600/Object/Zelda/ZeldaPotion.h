#pragma once
class ZeldaPotion
{
public :
	ZeldaPotion(Vector2 curframe);
	~ZeldaPotion();

	void Collider_Update();
	void Update();
	void Render();

	void SetPos(Vector2 pos) { _collider->SetPosition(pos); }

	void SetIsActive(bool value) { _isActive = value; }
	bool _isActive = true;
private :
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _collider;
};

