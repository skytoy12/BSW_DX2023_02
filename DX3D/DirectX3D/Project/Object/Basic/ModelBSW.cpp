#include "Framework.h"
#include "ModelBSW.h"

ModelBSW::ModelBSW()
{

    worldBuffer = new MatrixBuffer();

	reader = new ModelReader("Knight D Pelegrini");

    CreateMesh();

}

ModelBSW::~ModelBSW()
{
    delete worldBuffer;

    for (Material* material : materials)
        delete material;

    for (Mesh* mesh : meshes)
        delete mesh;

    for (ModelMesh* modelMesh : modelMeshes)
        delete modelMesh;

	delete reader;
}

void ModelBSW::Update()
{
    Transform::Update();

    worldBuffer->SetData(world);
}

void ModelBSW::Render()
{
    worldBuffer->SetVSBuffer(0);

    for (Material* material : materials)
    {
        material->SetShader(L"NormalMapping");
        material->SetMaterial();
    }


    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i]->SetMesh();
        DC->DrawIndexed(indexVector[i].size(), 0, 0);
    }


}

void ModelBSW::CreateMesh()
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

