#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(float radius, UINT sliceCount, UINT stackCount)
	:radius(radius), sliceCount(sliceCount), stackCount(stackCount)
{
	CreateMesh();

	mesh = new Mesh(vertices, indices);

	material = new Material();
	material->SetShader(L"Specular");

	worldBuffer = new MatrixBuffer();
}

Sphere::~Sphere()
{
	delete mesh;
	delete material;
	delete worldBuffer;
}


void Sphere::Render()
{
	worldBuffer->SetData(Transform::world);
	worldBuffer->SetVSBuffer(0);

	material->SetMaterial();
	mesh->SetMesh();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Sphere::CreateMesh()
{
	for (UINT i = 0; i < stackCount + 1; i++)
	{
		float phi = XM_PI / stackCount * i;

		for (UINT j = 0; j < sliceCount + 1; j++)
		{
			float theta = XM_2PI / sliceCount * j;

			VertexType vertex;

			vertex.pos.x = radius * sin(phi) * cos(theta);
			vertex.pos.y = radius * cos(phi);
			vertex.pos.z = radius * sin(phi) * sin(theta);

			vertex.normal = vertex.pos / radius;

			vertex.uv.x = j / (float)sliceCount;
			vertex.uv.y = i / (float)stackCount;

			vertices.push_back(vertex);
		}
	}

	for (UINT j = 0; j < stackCount; j++)
	{
		for (UINT i = 0; i < sliceCount; i++)
		{
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 1));

			indices.push_back(i + 0 + (sliceCount + 1) * (j + 1));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 1));
		}
	}
}
