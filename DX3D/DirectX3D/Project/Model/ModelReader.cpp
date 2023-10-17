#include "Framework.h"
#include "ModelReader.h"

ModelReader::ModelReader(string name)
	: name(name)
{
	ReadMaterial();
	ReadMesh();
}

ModelReader::~ModelReader()
{
	for (Material* material : materials)
		delete material;

	for (ModelMesh* mesh : meshes)
		delete mesh;

	materials.clear();
	meshes.clear();
}

void ModelReader::SetShader(wstring file)
{
	for (Material* material : materials)
		material->SetShader(file);
}

void ModelReader::Render()
{
	for (ModelMesh* mesh : meshes)
	{
		mesh->Render();
	}

}

void ModelReader::Debug()
{
	for (Material* material : materials)
		material->Debug();
}

void ModelReader::ReadMaterial()
{
	string path = "_ModelData/Material/" + name + "/MaterialList.list";

	BinaryReader data(ToWString(path));

	UINT size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		Material* material = new Material;

		string file = "_ModelData/Material/" + name + "/" + data.ReadString() + ".mat";

		material->Load(ToWString(file));

		materials.push_back(material);
	}
}

void ModelReader::ReadMesh()
{
	string path = "_ModelData/Mesh/" + name + ".mesh";

	BinaryReader data(ToWString(path));

	UINT size = data.ReadUINT();


	for (UINT i = 0; i < size; i++)
	{
		ModelMesh* mesh = new ModelMesh();
		mesh->name = data.ReadString();

		UINT materialIndex = data.ReadUINT();
		mesh->material = materials[materialIndex];

		{
			UINT count = data.ReadUINT();

			mesh->vertices.resize(count);

			void* ptr = mesh->vertices.data();

			data.ReadData(&ptr, sizeof(ModelVertex) * count);
		}
		{
			UINT count = data.ReadUINT();

			mesh->indices.resize(count);

			void* ptr = mesh->indices.data();

			data.ReadData(&ptr, sizeof(UINT) * count);
		}

		mesh->Create();

		meshes.push_back(mesh);
	}

	size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		NodeData node;

		node.index = data.ReadInt();
		node.name = data.ReadString();
		node.parent = data.ReadInt();
		node.transform = data.ReadMatrix();

		nodes.emplace_back(node);
	}

	size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		BoneData node;

		node.index = data.ReadInt();
		node.name = data.ReadString();
		node.offset = data.ReadMatrix();

		bones.emplace_back(node);

		boneMap.emplace(node.name, node.index);
	}
}
