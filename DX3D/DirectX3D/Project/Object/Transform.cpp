#include "Framework.h"
#include "Transform.h"


Transform::Transform()
{
	world = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	world = XMMatrixTransformation
	(
		pivot, XMQuaternionIdentity(), scale,
		pivot, XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z),
		translation
	);

	if (parent != nullptr)
		world *= parent->world;
}
