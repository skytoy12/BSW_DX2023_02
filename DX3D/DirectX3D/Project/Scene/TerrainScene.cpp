#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	material = new Material();
	material->SetShader(L"Texture");
	material->SetDuffuseMap(L"Landscape/Tree.png");

	worldBuffer = new MatrixBuffer();

	CreateMesh();
}

TerrainScene::~TerrainScene()
{
	delete mesh;
	delete worldBuffer;
	delete material;
}


void TerrainScene::Update()
{
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	worldBuffer->SetVSBuffer(0);

	    mesh->SetMesh();
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TerrainScene::PostRender()
{
}

void TerrainScene::CreateMesh()
{
	//Vertices
	for (float z = 0; z < height; z++)
	{
		for (float x = 0; x < width; x++)
		{
			VertexTexture vertex;
			vertex.pos = Vector3(x, 0, z);

			vertex.uv.x =     x / (width  - 1);
			vertex.uv.y = 1 - z / (height - 1);

			vertices.push_back(vertex);
		}
	}

	//Indices
	for (float z = 0; z < height - 1; z++)
	{
		for (float x = 0; x < width - 1; x++)
		{
			indices.push_back((x + 0) + width * (z + 1));  //7
			indices.push_back((x + 1) + width * (z + 1));  //8
			indices.push_back((x + 0) + width * (z + 0));  //0

			indices.push_back((x + 0) + width * (z + 0));  //0
			indices.push_back((x + 1) + width * (z + 1));  //8
			indices.push_back((x + 1) + width * (z + 0));  //1
		}
	}
	mesh = new Mesh(vertices, indices);
}