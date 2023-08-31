#pragma once
class TerrainScene : public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateMesh();
private:
	vector<VertexTexture> vertices;
	vector<UINT>           indices;

	Material* material;
	Mesh* mesh;

	MatrixBuffer* worldBuffer;

	UINT width  = 10;
	UINT height = 10;

	Texture* heightMap;

	const float MAP_HEIGHT = 20.0f;
};


