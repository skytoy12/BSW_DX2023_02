#pragma once



class TerrainEditor : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	TerrainEditor(UINT height = 100, UINT width = 100);
	~TerrainEditor();

	void Update();
	void Render();

	void Debug();

	Material* GetMaterial() { return material; }

	bool Picking(OUT Vector3* position);

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();
private:
	vector<VertexType> vertices;
	vector<UINT>           indices;

	Material* material;
	Mesh* mesh;

	MatrixBuffer* worldBuffer;

	UINT width ;
	UINT height;

	Texture* heightMap;

	const float MAP_HEIGHT = 20.0f;

};


