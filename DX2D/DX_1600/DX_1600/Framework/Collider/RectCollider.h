#pragma once
class RectCollider : public Collider
{

private :
	struct AABBRectInfo
	{
		float left = 0.0f;
		float top = 0.0f;
		float right = 0.0f;
		float bottom = 0.0f;
	};

	struct OBBRectinfo
	{
		Vector2 worldPos;
		Vector2 direction[2]; // 가로 세로 벡터
		float length[2]; // 가로 세로 길이
	};

public :
	RectCollider(Vector2 size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;

	void SetScale(Vector2 scale) { _transform->SetScale(scale); }

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	Vector2 GetWorldSize() { return { _size.x * _transform->GetWorldScale().x, _size.y * _transform->GetWorldScale().y }; }

	AABBRectInfo GetAABBInfo();
	OBBRectinfo GetOBBInfo();

	// Matrix 상속 걸려있는 구조에선 Block X
	bool Block(shared_ptr<RectCollider> moveable);
	bool Block(shared_ptr<class CircleCollider> moveable);




private :
	Vector2 _size;

};

