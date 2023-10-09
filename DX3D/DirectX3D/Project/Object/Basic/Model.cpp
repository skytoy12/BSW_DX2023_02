#include "Framework.h"
#include "Model.h"

Model::Model()
{

    worldBuffer = new MatrixBuffer();

	reader = new ModelReader("Knight D Pelegrini");

    CreateMesh();

}

Model::~Model()
{
    for (Material* material : materials)
        delete material;

    for (Mesh* mesh : meshes)
        delete mesh;

    for (ModelMesh* modelMesh : modelMeshes)
        delete modelMesh;

	delete reader;
    delete worldBuffer;
}

void Model::Update()
{
    Transform::Update();

    worldBuffer->SetData(world);
}

void Model::Render()
{
    for (Material* material : materials)
    {
        material->SetShader(L"NormalMapping");
        material->SetMaterial();
    }


    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i]->SetMesh();
        DC->DrawIndexed(indexVector[0].size(), 0, 0);
    }

    worldBuffer->SetVSBuffer(0);

}

void Model::CreateMesh()
{
    for (int i = 0; i < reader->GetMaterials().size(); i++)
    {
        materials.push_back(reader->GetMaterials()[i]);
    }

    for (int i = 0; i < reader->GetModelMeshes().size(); i++)
    {
        modelMeshes.push_back(reader->GetModelMeshes()[i]);
    }
    
    for (int i = 0; i < reader->GetModelMeshes().size(); i++)
    {
        for (int j = 0; j < modelMeshes[i]->GetVertices().size(); j++)
        {
            ModelVertex temp1 = modelMeshes[i]->GetVertices()[j];
            vertices.push_back(temp1);
        }

        for (int k = 0; k < modelMeshes[i]->GetIndices().size(); k++)
        {
            UINT temp2 = modelMeshes[i]->GetIndices()[k];
            indices.push_back(temp2);
        }

        Mesh* mesh = new Mesh(vertices, indices);

        indexVector.push_back(indices);

        meshes.push_back(mesh);

        vertices.clear();
        indices.clear();

    }

}

