#pragma once

class ModelMesh
{
	friend class ModelReader;
public:
	ModelMesh();
	~ModelMesh();

private:
	string name;

	UINT materialIndex;

	Material* material;

	Mesh* mesh;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;

};


