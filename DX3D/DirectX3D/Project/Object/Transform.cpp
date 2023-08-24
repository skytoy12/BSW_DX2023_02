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

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);

	right   = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	up      = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();

	XMVECTOR outS, outR, outT;
	XMMatrixDecompose(&outS, &outR, &outT, world);

	globalScale    = outS;
	globalRotation = outR;
	globalPosition = outT;
}
