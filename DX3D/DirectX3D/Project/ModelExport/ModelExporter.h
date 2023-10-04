#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportMaterial();

	wstring CreateTexture(string file);
private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<Material*> materials;
};



