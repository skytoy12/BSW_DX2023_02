#pragma once

class ModelMesh
{
	friend class ModelReader;
public:
	ModelMesh();
	~ModelMesh();
	vector<ModelVertex> GetVertices() { return vertices; }
	vector<UINT> GetIndices() { return indices; }

private:
	string name;

	UINT materialIndex;

	Material* material;

	Mesh* mesh;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;

};


