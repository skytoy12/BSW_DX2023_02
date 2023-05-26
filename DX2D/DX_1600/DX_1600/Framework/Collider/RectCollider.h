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

	void Block(shared_ptr<RectCollider> moveable);




private :
	Vector2 _size;

};

