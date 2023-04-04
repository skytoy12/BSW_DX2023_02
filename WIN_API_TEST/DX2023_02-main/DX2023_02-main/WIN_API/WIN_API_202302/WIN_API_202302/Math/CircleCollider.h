#pragma once
class RectCollider;

class CircleCollider : public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(Vector2 center, float radius);
	~CircleCollider();

	void Update();
	void Render(HDC hdc);

	void MoveCenter(const Vector2& value);

	void SetCenter(const Vector2& value);
	const Vector2& GetCenter() { return _center; }

	void SetRadius(float radius);
	const float& GetRadius() { return _radius; }

	void SetGreen() { _curPenIndex = 0; }
	void SetRed() { _curPenIndex = 1; }

	bool IsCollision(Vector2 pos);
	bool IsCollision(shared_ptr<CircleCollider> other);
	bool IsCollision(shared_ptr<RectCollider> other);

private:
	vector<HPEN> _pens;
	UINT _curPenIndex = 0;

	Vector2 _center = { 0.0f,0.0f };
	float _radius = 0;
};

