#pragma once
class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	void Render();

	void Debug();

	vector<Material*> GetMaterials() { return materials; }
	vector<ModelMesh*> GetModelMeshes() { return meshes; }

private:
	void ReadMaterial();
	void ReadMesh();

private :
	string name;

	vector<Material*> materials;
	vector<ModelMesh*> meshes;
};



