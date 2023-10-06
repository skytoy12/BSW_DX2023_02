#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportModel();

private :

	void ExportMaterial();
	void ExportMesh();

	wstring CreateTexture(string file);

	void  ReadMesh(aiNode* node);
	void WriteMesh();


private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<MeshData*> meshes;

	vector<string> materialNames;
};



