#pragma once
class Terrain : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Terrain(wstring diffuseFile, wstring specularFile, wstring NormalFile, wstring heightFile);
	Terrain(wstring diffuseFile, wstring heightFile);
	~Terrain();

	void Render();

	Material* GetMaterial() { return material; }

	bool Picking(OUT Vector3* position);
	bool EditPicking(OUT Vector3* position);

	float GetHeight(Vector3 position);

private :
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();
	void CreateCompute();
private:
	vector<VertexType> vertices;
	vector<UINT>           indices;

	Material* material;
	Mesh* mesh;

	////////////////////////////////////////

	struct InputDesc
	{
		UINT index;

		Vector3 v0, v1, v2;
	};

	struct OutputDesc
	{
		int isPicked;

		float u, v;

		float distance;
	};

	StructuredBuffer* structuredBuffer;
	RayBuffer* rayBuffer;

	ComputeShader* computeShader;
	UINT polygonCount;

	InputDesc* input;
	OutputDesc* output;
	////////////////////////////////////////

	MatrixBuffer* worldBuffer;

	UINT width = 10;
	UINT height = 10;

	Texture* heightMap;

	const float MAP_HEIGHT = 20.0f;
};

