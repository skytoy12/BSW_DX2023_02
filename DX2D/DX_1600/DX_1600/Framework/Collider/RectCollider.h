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

	Vector2 GetWorldSize() { return { _size.x * _transform->GetWorldScale().x, _size.y * _transform->GetWorldScale().y }; }

	AABBRectInfo GetAABBInfo();
	OBBRectinfo GetOBBInfo();


	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;





	// Matrix 상속 걸려있는 구조에선 Block X
	bool Block(shared_ptr<RectCollider> moveable);
	bool Block(shared_ptr<class CircleCollider> moveable);




private :
	virtual bool AABB_Collision(shared_ptr<RectCollider> other) override final;
	virtual bool AABB_Collision(shared_ptr<CircleCollider> other) override final;

	virtual bool OBB_Collision(shared_ptr<RectCollider> other) override final;
	virtual bool OBB_Collision(shared_ptr<CircleCollider> other) override final;

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
	{
		float r1 = abs(separate.Dot(e1));
		float r2 = abs(separate.Dot(e2));

		return r1 + r2;
	}

	Vector2 _size;
};

