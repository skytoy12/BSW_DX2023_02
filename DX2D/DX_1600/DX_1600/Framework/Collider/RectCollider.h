#pragma once
class RectCollider : public Collider
{
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

	float WorldLeft() { return _transform->GetWorldPosition().x - (GetWorldSize().x * 0.5); }
	float WorldRight() { return _transform->GetWorldPosition().x + (GetWorldSize().x * 0.5); }
	float WorldTop() { return _transform->GetWorldPosition().y + (GetWorldSize().y * 0.5); }
	float WorldBottom() { return _transform->GetWorldPosition().y - (GetWorldSize().y * 0.5); }


private :
	Vector2 _size;

};

