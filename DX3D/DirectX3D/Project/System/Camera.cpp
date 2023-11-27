#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();
	
	translation = { 40.0f, 100.0f, -80.0f };
	rotation.x = 0.6f;

	Load();
}

Camera::~Camera()
{
	Save();

	delete viewBuffer;
}

void Camera::Update()
{
	CalculateFrustum();

	if (target == nullptr)
		FreeMode();
	else
		TargetMode(MODE2);
}

void Camera::Debug()
{
	ImGuiIO io = ImGui::GetIO();
	distance -= io.MouseWheel * moveSpeed;

	if (ImGui::TreeNode("Camera Option"))
	{
		Vector3 pos = translation;
		Vector3 rot = rotation;

		ImGui::Text("Camera Pos : %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
		ImGui::Text("Camera Rot : %.3f, %.3f, %.3f", rot.x, rot.y, rot.z);

		Transform::Debug();

		ImGui::SliderFloat("Height", &height, -10.0f, 100.0f);
		ImGui::SliderFloat("Distance", &distance, -10.0f, 100.0f);

		ImGui::SliderFloat("Camera MoveDamping", &moveDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera  RotDamping", &rotDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera  RotY", &rotY, 0, XM_2PI);

		ImGui::TreePop();
	}

	//ImGui::Text("Camera MousePos : %.3f, %.3f, %.3f", mousePos.x, mousePos.y, mousePos.z);
	//ImGui::Text("Camera OldPos : %.3f, %.3f, %.3f", oldPos.x, oldPos.y, oldPos.z);
	//ImGui::Text("Camera Dir : %.3f, %.3f, %.3f", cameraDir.x, cameraDir.y, cameraDir.z);

	//if (ImGui::Button("GrootOrigin"))
	//{
	//	Transform::translation = { -44.0f, 174.0f, -203.0f };
	//	Transform::rotation.x = 0.5f;
	//	Transform::rotation.y = 0.2f;
	//	Transform::rotation.z = 0.0f;
	//}

}

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
	Ray ray;
	ray.origin = translation;

	///////////////////InvViewport//////////////////////

	Vector3 point;

	point.x = +(2.0f * screenPos.x) / WIN_WIDTH - 1.0f;
	point.y = -(2.0f * screenPos.y) / WIN_HEIGHT + 1.0f;
	point.z =   1.0f; // farZ

	///////////////////InvProjection////////////////////

	Matrix projection = Environment::GetInstance()->GetPersMatrix();

	XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, projection);

	point.x /= proj._11;
	point.y /= proj._22;

	///////////////////InvView////////////////////

	Matrix invView = GetWorld(); // camea의 view자체가 역행열이므로 view의 역행열은 그냥 World

	ray.direction = point * invView;
	ray.direction.Normalize();

	return ray;
}

Vector3 Camera::WorldToScreenPoint(Vector3 worldPos)
{
	Vector3 screenPos;

	screenPos = XMVector3TransformCoord(worldPos, viewMatrix);
	screenPos = XMVector3TransformCoord(screenPos, Environment::GetInstance()->GetPersMatrix());

	screenPos = (screenPos + Vector3(1.0f, 1.0f, 1.0f)) * 0.5f;

	screenPos.x *= WIN_WIDTH;
	screenPos.y *= WIN_HEIGHT;

	return screenPos;
}

bool Camera::ContainPoint(Vector3 point)
{
	for (UINT i = 0; i < 6; i++)
	{
		Vector3 dot = XMPlaneDotCoord(planes[i], point);

		if (dot.x < 0.0f)
			return false;
	}

	return true;
}

bool Camera::ContainSphere(Vector3 center, float radius)
{
	Vector3 edge;
	Vector3  dot;

	for (UINT i = 0; i < 6; i++)
	{
		edge.x = center.x - radius;
		edge.y = center.y - radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y - radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y + radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y - radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y + radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y - radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y + radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y + radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		return false;
	}

	return true;
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS(VK_LSHIFT))
			moveSpeed = 50.0f;
		else
			moveSpeed = 20.0f;

		if (KEY_PRESS('A'))
			translation += Left()     * moveSpeed * Time::Delta();
		if (KEY_PRESS('D'))					   
			translation += Right()    * moveSpeed * Time::Delta();
		if (KEY_PRESS('S'))
			translation += Backward() * moveSpeed * Time::Delta();
		if (KEY_PRESS('W'))
			translation += Forward()  * moveSpeed * Time::Delta();
		if (KEY_PRESS('Q'))
			translation += Up()       * moveSpeed * Time::Delta();
		if (KEY_PRESS('E'))				       
			translation += Down()     * moveSpeed * Time::Delta();

		Vector3 dir = mousePos - oldPos;

		if (abs(dir.x) > 10.0f || abs(dir.y) > 10.0f)
		{
			dir.x = 0.0f;
			dir.y = 0.0f;
		}

		if (dir.x != 0.0f)
			cameraDir.x = dir.x;
		if (dir.y != 0.0f)
			cameraDir.y = dir.y;
		if (dir.z != 0.0f)
			cameraDir.z = dir.z;

		Transform::rotation.y += dir.x * rotSpeed * 0.0005f;//Time::Delta();
		Transform::rotation.x += dir.y * rotSpeed * 0.0005f;//Time::Delta();
	}

	oldPos = mousePos;

	viewMatrix = XMMatrixInverse(nullptr, Transform::GetWorld());

	SetView();
}

void Camera::TargetMode(Mode mode)
{
	if (KEY_PRESS(VK_UP))
		height += moveSpeed * Time::Delta();

	if (KEY_PRESS(VK_DOWN))
		height -= moveSpeed * Time::Delta();

	switch (mode)
	{
	case Camera::MODE1:
	{
		destRotY = LERP(destRotY, target->rotation.y, rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationY(destRotY + rotY);

		Vector3 forward = V_FORWARD * rotMatrix;

		destination = target->GetGlobalPosition() + forward * distance + V_UP * height;

		Transform::translation = LERP(Transform::translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(Transform::translation, target->translation, V_UP);
	}
		break;

	case Camera::MODE2:
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			Vector3 dir = mousePos - oldPos;

			Transform::rotation.y += dir.x * rotSpeed * Time::Delta();
			Transform::rotation.x += dir.y * rotSpeed * Time::Delta();
		}
		oldPos = mousePos;

		destRotY = LERP(destRotY, Transform::rotation.y, rotDamping * Time::Delta());
		destRotX = LERP(destRotX, Transform::rotation.x, rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(destRotX, destRotY + rotY, 0.0f);

		Vector3 forward = V_FORWARD * rotMatrix;

		destination = target->GetGlobalPosition() + forward * distance;

		Transform::translation = LERP(Transform::translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(Transform::translation, target->translation, V_UP);

		viewMatrix *= XMMatrixTranslation(0, -height, 0);
	}
	    break;
	default:
		break;
	}

	//destination = target->translation - target->Backward() * distance + V_UP * height;

	//Transform::translation = destination;

	//viewMatrix = XMMatrixLookAtLH(destination, target->translation, V_UP);

	////////////////////////////////////////////////////////////////////////////////////////

	//destination = target->translation - V_FORWARD * distance + V_UP * height;

	//Transform::translation = destination;

	//viewMatrix = XMMatrixLookAtLH(destination, target->translation, V_UP);

	SetView();
}

void Camera::SetView()
{
	Transform::Update();

	//XMVECTOR   eyePos = Transform::translation;
	//XMVECTOR focusPos = Transform::translation + Transform::Forward();
	//XMVECTOR upVector = Transform::Up();

	//viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	viewMatrix = XMMatrixInverse(nullptr, world);
	viewBuffer->SetData(viewMatrix, Transform::GetWorld());
	viewBuffer->SetVSBuffer(1);
}

void Camera::Set()
{
	viewMatrix = XMMatrixInverse(nullptr, world);
	viewBuffer->SetData(viewMatrix, Transform::GetWorld());
}

void Camera::Save()
{
	BinaryWriter data(L"CameraData");

	data.WriteData(Transform::scale);
	data.WriteData(Transform::rotation);
	data.WriteData(Transform::translation);
}

void Camera::Load()
{
	BinaryReader data(L"CameraData");

	if (!data.Succeeded())
		return;

	Transform::scale = data.ReadVector3();
	Transform::rotation = data.ReadVector3();
	Transform::translation = data.ReadVector3();
}

void Camera::CalculateFrustum()
{
	XMFLOAT4X4 VP;
	XMStoreFloat4x4(&VP, viewMatrix * Environment::GetInstance()->GetPersMatrix());

	//Left
	a = VP._14 + VP._11;
	b = VP._24 + VP._21;
	c = VP._34 + VP._31;
	d = VP._44 + VP._41;

	planes[0] = XMVectorSet(a, b, c, d);

	//Right
	a = VP._14 - VP._11;
	b = VP._24 - VP._21;
	c = VP._34 - VP._31;
	d = VP._44 - VP._41;

	planes[1] = XMVectorSet(a, b, c, d);

	//Bottom
	a = VP._14 + VP._12;
	b = VP._24 + VP._22;
	c = VP._34 + VP._32;
	d = VP._44 + VP._42;

	planes[2] = XMVectorSet(a, b, c, d);

	//Top
	a = VP._14 - VP._12;
	b = VP._24 - VP._22;
	c = VP._34 - VP._32;
	d = VP._44 - VP._42;

	planes[3] = XMVectorSet(a, b, c, d);

	//Near
	a = VP._14 + VP._13;
	b = VP._24 + VP._23;
	c = VP._34 + VP._33;
	d = VP._44 + VP._43;

	planes[4] = XMVectorSet(a, b, c, d);

	//Near
	a = VP._14 - VP._13;
	b = VP._24 - VP._23;
	c = VP._34 - VP._33;
	d = VP._44 - VP._43;

	planes[5] = XMVectorSet(a, b, c, d);

	for (UINT i = 0; i < 6; i++)
	{
		planes[i] = XMPlaneNormalize(planes[i]);
	}
}
