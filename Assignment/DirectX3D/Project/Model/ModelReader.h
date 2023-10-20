#pragma once
class ModelReader
{
	friend class ModelAnimation;
	friend class ModelAnimator;
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	void Render();

	void Debug();

	bool HasBone(string boneName) { return boneMap.count(boneName) > 0; }

	vector<Material*> GetMaterials() { return materials; }

	UINT GetBoneIndex(string name);
	UINT GetNodeIndex(string name);

private:
	void ReadMaterial();
	void ReadMesh();

private :
	string name;

	vector<Material*> materials;
	vector<ModelMesh*> meshes;

	vector<NodeData> nodes;
	vector<BoneData> bones;

	map<string, UINT> boneMap;
};



