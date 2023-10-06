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

	//data.WriteData(mesh->name);
	//data.WriteData(mesh->materialIndex);
	
	//data.WriteData((UINT)mesh->vertices.size());
	//data.WriteData(mesh->vertices.data(), mesh->vertices.size() * sizeof(ModelVertex));
	
	//data.WriteData((UINT)mesh->indices.size());
	//data.WriteData(mesh->indices.data(), mesh->indices.size() * sizeof(UINT));

	for (UINT i = 0; i < size; i++)
	{
		ModelMesh* mesh = new ModelMesh();
		mesh->name = data.ReadString();
		mesh->materialIndex = data.ReadUINT();

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

		meshes.push_back(mesh);
	}
}
