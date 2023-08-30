#pragma once
class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public :
	CircleCollider(float radius);
	~CircleCollider();

	virtual void Update() override;
	virtual void Render() override;


	virtual void CreateVertices() override;


	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;

	

	// Rect와 공유하지 않는 함수
	void SetScale(float value) { _transform->SetScale({ value, value }); }
	void reverseScale() { _transform->SetScale({ -1, 1 }); }
	void OriginScale() { _transform->SetScale({ 1, 1 }); }
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * abs(_transform->GetWorldScale().x); }
	
	void SetIsActive(bool isActive) { _isActive = isActive; }
	bool GetISActive() { return _isActive; }

	// Matrix 상속 걸려있는 구조에선 Block X
	virtual bool Block(shared_ptr<CircleCollider> moveable) override;
	virtual bool Block(shared_ptr<class RectCollider> moveable) override;

	float Angle(float angle) { return angle * (PI / 180); }

protected :
	bool AABB_Collision(shared_ptr<RectCollider> other) override final;
	bool AABB_Collision(shared_ptr<CircleCollider> other) override final;

	bool OBB_Collision(shared_ptr<RectCollider> other) override final;
	bool OBB_Collision(shared_ptr<CircleCollider> other) override final;

	float _radius;

	bool _isActive = true;

};

