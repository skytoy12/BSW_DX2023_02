#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	bullet.origin = translation;
	bullet.direction = Forward();

	material = new Material(L"03Collider");
	CreateMesh();

	SetColor(1.0f, 0.0f, 0.0f);
}

Bullet::~Bullet()
{
}

void Bullet::CreateMesh()
{
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
		vertices[0] = { bullet.origin.x, bullet.origin.y, bullet.origin.z };
		vertices[1] = { destination.x, destination.y, destination.z };
	}

	if (bulletActive == false)
	{
		mesh->UpdateVertex(vertices.data(), vertices.size());
	}

	if (bulletActive == true)
	{
		activeTime += Time::Delta();
		if (activeTime > 0.3f)
		{
			bulletActive = false;
			activeTime = 0.0f;
		}
	}

}

void Bullet::Render()
{
	Transform::SetWorld();

	if (bulletActive == false)
		return;

	mesh->SetMesh(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Bullet::Debug()
{

}


