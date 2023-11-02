#pragma once

class ModelMesh
{
	friend class ModelReader;
public:
	ModelMesh();
	~ModelMesh();

	void Create();

	void Render();

	void RenderInstanced(UINT instancedCount);

	vector<ModelVertex> GetVertices() { return vertices; }
	vector<UINT> GetIndices() { return indices; }

private:
	string name;

	Material* material;

	Mesh* mesh;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;

};


