#include "Framework.h"
#include "ColliderSphere.h"

ColliderSphere::ColliderSphere(float radius, UINT stackCount, UINT sliceCount)
	: radius(radius), stackCount(stackCount), sliceCount(sliceCount)
{
	type = SPHERE;

	CreateMesh();
}

ColliderSphere::~ColliderSphere()
{
}

bool ColliderSphere::Collision(IN Ray& ray, OUT Contact* contact)
{
	return false;
}

bool ColliderSphere::Collision(ColliderBox* other)
{
	return false;
}

bool ColliderSphere::Collision(ColliderSphere* other)
{
	float distance = Distance(this->globalPosition, other->globalPosition);

	return distance <= this->Radius() + other->Radius();
}

bool ColliderSphere::Collision(ColliderCapsule* other)
{
	return false;
}

void ColliderSphere::CreateMesh()
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

			vertices.push_back(vertex);
		}
	}

	for (UINT j = 0; j < stackCount; j++)
	{
		for (UINT i = 0; i < sliceCount; i++)
		{
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 0));

			indices.push_back(i + 0 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 1));
		}
	}

	mesh = new Mesh(vertices, indices);
}
