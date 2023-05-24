#pragma once
class RectCollider
{
public :
	RectCollider(Vector2 size);
	~RectCollider();

	void Update();
	void Render();

	void CreatData();
	void CreateVertices();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }

	void SetScale(Vector2 scale) { _transform->SetScale(scale); }

	const shared_ptr<Transform> GetTransform() { return _transform; }
	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

private :
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

	Vector2 _size;
};

