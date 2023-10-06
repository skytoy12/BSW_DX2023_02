#pragma once
class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

private:
	void ReadMaterial();
	void ReadMesh();

private :
	string name;

	vector<Material*> materials;
	vector<ModelMesh*> meshes;
};



