#pragma once
class Sphere : public Transform
{
	typedef VertexTextureNormal VertexType;
public :
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere();

	void Render();

private :
	void CreateMesh();

private :
	Material* material = nullptr;
	Mesh*         mesh = nullptr;

	vector<VertexType> vertices;
	vector<UINT>           indices;

	MatrixBuffer* worldBuffer = nullptr;


	float radius;
	UINT sliceCount;
	UINT stackCount;
};

