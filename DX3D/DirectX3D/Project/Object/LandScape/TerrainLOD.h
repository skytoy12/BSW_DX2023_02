#pragma once
class TerrainLOD : public Transform
{
private :
	typedef VertexTexture VertexType;

public:
	TerrainLOD(wstring heightMap);
	~TerrainLOD();

	void Render();
	void Debug();

private:
	void CreateMesh();

private :
	UINT width, height;

	UINT patchWidth, patchHeight;

	UINT cellsPerPatch = 32;
	float cellSpacing = 5.0f;
	Vector2 cellUV;

	Material* material;
	Mesh* mesh;

	vector<VertexType> vertices;
	vector<UINT> indices;

	Texture* heightMap;

	FloatValueBuffer* terrainBuffer;
	FloatValueBuffer* heightBuffer;

	HullShader*     hullShader;
	DomainShader* domainShader;
};
