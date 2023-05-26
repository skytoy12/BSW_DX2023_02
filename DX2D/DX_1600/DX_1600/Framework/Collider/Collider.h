#pragma once
class CircleCollider;
class RectCollider;

class Collider
{

protected :
	enum class ColliderType
	{
		NONE,
		CIRCLE,
		RECT
	};

public :


	Collider(ColliderType type);
	virtual ~Collider();

	virtual void Update();
	virtual void Render();
	virtual void CreateVertices() abstract;
	void CreatData();


	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }



	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	Vector2 GetPos() { return _transform->GetPos(); }


	virtual bool IsCollision(Vector2 pos) abstract;
	bool IsCollision(shared_ptr<Collider> col);
	virtual bool IsCollision(shared_ptr<CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> other) abstract;

	const shared_ptr<Transform> GetTransform() { return _transform; }

	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

	

protected :

	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

	ColliderType _type;
};

