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
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	// Rect�� �������� �ʴ� �Լ�
	void SetSCale(float value) { _transform->SetScale({ value, value }); }
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }
	
	void SetIsActive(bool isActive) { _isActive = isActive; }
	bool GetISActive() { return _isActive; }

	// Matrix ��� �ɷ��ִ� �������� Block X
	bool Block(shared_ptr<CircleCollider> moveable);

	float Angle(float angle) { return angle * (PI / 180); }

protected :

	float _radius;

	bool _isActive = true;

};

