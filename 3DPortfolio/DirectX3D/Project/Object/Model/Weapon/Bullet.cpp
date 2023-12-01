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
	if (isActive == false)
		return;

	if (target != nullptr)
	{
		vertices[0] = { bullet.origin.x, bullet.origin.y, bullet.origin.z };
		vertices[1] = { destination.x, destination.y, destination.z };
	}
	bullet.origin.x = LERP(bullet.origin.x, destination.x, 200.0f);
	bullet.origin.y = LERP(bullet.origin.y, destination.y, 200.0f);
	bullet.origin.z = LERP(bullet.origin.z, destination.z, 200.0f);

	mesh->UpdateVertex(vertices.data(), vertices.size());
}

void Bullet::Render()
{
	Transform::SetWorld();

	if (isActive == false)
		return;

	mesh->SetMesh(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Bullet::Debug()
{

}


