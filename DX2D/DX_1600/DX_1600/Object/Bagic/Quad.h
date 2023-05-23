#pragma once
class Quad
{
public :
	Quad();
	Quad(wstring srvFile);
	~Quad();
	
	virtual void Update();
	virtual void Render();

	virtual void CreateVertices();

	virtual shared_ptr<Transform> GetTransform() { return _transform; }


protected :
	// Á¤Á¡(pos, color, uv) 6°³
	vector<Vertex_Texture> _vertices;
	vector<UINT> _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SRV> _srv;

	shared_ptr<Transform> _transform;
};

