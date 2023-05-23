#pragma once
class CircleCollider
{
public :
	CircleCollider(float radius);
	~CircleCollider();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

	void CreateData();
	void CreateVertices();

	float Angle(float angle) { return angle * (PI / 180); }

private :
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	float _radius;
};

