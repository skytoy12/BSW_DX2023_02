#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	bullet.origin = translation;
	bullet.direction = Forward();

	material = new Material(L"03Collider");
	CreateMesh();

	SetColor(0.0f, 0.0f, 0.0f);
}

Bullet::~Bullet()
{
}

void Bullet::CreateMesh()
{
	Vector3 destination;
	destination = bullet.origin + (bullet.direction * range);

	vertices =
	{
		{ bullet.origin.x, bullet.origin.y, bullet.origin.z },
		{ destination.x, destination.y, destination.z }
	};

	indices =
	{
		0,1
	};

	mesh = new Mesh(vertices, indices);
}

void Bullet::Update()
{
	if (target != nullptr)
	{
		bullet.origin = target->translation;
		bullet.origin.y = 5.0f;
		//bullet.direction = target->Forward() * -1.0f;

		Vector3 destination;
		destination = bullet.origin + (bullet.direction * range);

		vertices[0] = { bullet.origin.x, bullet.origin.y, bullet.origin.z };
		vertices[1] = { destination.x, destination.y, destination.z };
	}


	mesh->UpdateVertex(vertices.data(), vertices.size());
}

void Bullet::Render()
{
	Transform::SetWorld();

	mesh->SetMesh(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Bullet::SetRay(Vector3 origin, Vector3 direction)
{
	bullet.origin = origin;
	bullet.direction = direction;
}
