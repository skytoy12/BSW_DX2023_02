#pragma once
class ModelBSW : public Transform
{

public:
    ModelBSW();
	~ModelBSW();

    void Update();
    void Render();

    void CreateMesh();
private:

    vector<Material*> materials;
    vector<Mesh*> meshes;


    MatrixBuffer* worldBuffer;


    vector<ModelVertex> vertices;
    vector<UINT>         indices;

    vector<vector<UINT>> indexVector;


    vector<ModelMesh*> modelMeshes;

    ModelReader* reader;
};


