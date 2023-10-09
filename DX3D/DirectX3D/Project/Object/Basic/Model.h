#pragma once
class Model : public Transform
{

public:
	Model();
	~Model();

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


