#pragma once
class Collider
{
public :
	enum class ColliderType
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider();
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void CreatData() abstract;
	virtual void CreateVertices() abstract;

private :
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

	ColliderType _type;
};

