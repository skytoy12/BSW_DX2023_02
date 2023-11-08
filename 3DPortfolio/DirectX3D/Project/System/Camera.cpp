#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();
	
	transform = new Transform();

	transform->translation = { 40.0f, 100.0f, -80.0f };
	transform->rotation.x = 0.6f;

	Load();
}

Camera::~Camera()
{
	Save();

	delete transform;
	delete viewBuffer;
}

void Camera::Update()
{
	if (target == nullptr)
		FreeMode(MODE3);
	else
		TargetMode(mode);
}

void Camera::Debug()
{
	ImGuiIO io = ImGui::GetIO();
	distance -= io.MouseWheel * moveSpeed;

	if (ImGui::TreeNode("Camera Option"))
	{
		Vector3 pos = transform->translation;
		Vector3 rot = transform->rotation;

		ImGui::Text("Camera Pos : %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
		ImGui::Text("Camera Rot : %.3f, %.3f, %.3f", rot.x, rot.y, rot.z);

		transform->Debug();

		ImGui::SliderFloat("Height", &height, -10.0f, 100.0f);
		ImGui::SliderFloat("Distance", &distance, -10.0f, 100.0f);

		ImGui::SliderFloat("Camera MoveDamping", &moveDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera  RotDamping", &rotDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera  RotY", &rotY, 0, XM_2PI);
		ImGui::SliderFloat("Camera  RotX", &rotX, 0, XM_2PI);

		ImGui::TreePop();
	}

	//ImGui::Text("Camera MousePos : %.3f, %.3f, %.3f", mousePos.x, mousePos.y, mousePos.z);
	//ImGui::Text("Camera OldPos : %.3f, %.3f, %.3f", oldPos.x, oldPos.y, oldPos.z);
	//ImGui::Text("Camera Dir : %.3f, %.3f, %.3f", cameraDir.x, cameraDir.y, cameraDir.z);

	//if (ImGui::Button("GrootOrigin"))
	//{
	//	transform->translation = { -44.0f, 174.0f, -203.0f };
	//	transform->rotation.x = 0.5f;
	//	transform->rotation.y = 0.2f;
	//	transform->rotation.z = 0.0f;
	//}

}

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
	Ray ray;
	ray.origin = transform->translation;

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

	Matrix invView = transform->GetWorld(); // camea의 view자체가 역행열이므로 view의 역행열은 그냥 World

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


void Camera::FreeMode(Mode mode)
{

	switch (mode)
	{
	case Camera::MODE1:
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			if (KEY_PRESS(VK_LSHIFT))
				moveSpeed = 50.0f;
			else
				moveSpeed = 20.0f;

			if (KEY_PRESS('A'))
				transform->translation += transform->Left() * moveSpeed * Time::Delta();
			if (KEY_PRESS('D'))
				transform->translation += transform->Right() * moveSpeed * Time::Delta();
			if (KEY_PRESS('S'))
				transform->translation += transform->Backward() * moveSpeed * Time::Delta();
			if (KEY_PRESS('W'))
				transform->translation += transform->Forward() * moveSpeed * Time::Delta();
			if (KEY_PRESS('Q'))
				transform->translation += transform->Up() * moveSpeed * Time::Delta();
			if (KEY_PRESS('E'))
				transform->translation += transform->Down() * moveSpeed * Time::Delta();

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

			transform->rotation.y += dir.x * rotSpeed * 0.0005f;//Time::Delta();
			transform->rotation.x += dir.y * rotSpeed * 0.0005f;//Time::Delta();
		}

		oldPos = mousePos;

		viewMatrix = XMMatrixInverse(nullptr, transform->GetWorld());
	}
	break;

	case Camera::MODE2:
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			if (KEY_PRESS(VK_LSHIFT))
				moveSpeed = 50.0f;
			else
				moveSpeed = 20.0f;

			if (KEY_PRESS('A'))
				transform->translation += transform->Left() * moveSpeed * Time::Delta();
			if (KEY_PRESS('D'))
				transform->translation += transform->Right() * moveSpeed * Time::Delta();
			if (KEY_PRESS('S'))
				transform->translation += transform->Backward() * moveSpeed * Time::Delta();
			if (KEY_PRESS('W'))
				transform->translation += transform->Forward() * moveSpeed * Time::Delta();
			if (KEY_PRESS('Q'))
				transform->translation += transform->Up() * moveSpeed * Time::Delta();
			if (KEY_PRESS('E'))
				transform->translation += transform->Down() * moveSpeed * Time::Delta();

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

			transform->rotation.y += dir.x * rotSpeed * 0.0005f;//Time::Delta();
			transform->rotation.x += dir.y * rotSpeed * 0.0005f;//Time::Delta();
		}

		oldPos = mousePos;

		viewMatrix = XMMatrixInverse(nullptr, transform->GetWorld());
	}
	break;
	case Camera::MODE3:
	{
		if (KEY_PRESS(VK_LSHIFT))
			moveSpeed = 50.0f;
		else
			moveSpeed = 20.0f;


		float moveRange = 50.0f;

		if (mousePos.x < moveRange)
			transform->translation += transform->Left() * moveSpeed * Time::Delta();
		if (mousePos.x > WIN_WIDTH - moveRange)
			transform->translation += transform->Right() * moveSpeed * Time::Delta();

		Vector3 dirZ1 = transform->Backward();
		dirZ1.y = 0;

		Vector3 dirZ2 = transform->Forward();
		dirZ2.y = 0;

		if (mousePos.y > WIN_HEIGHT - moveRange)
			transform->translation += dirZ1 * moveSpeed * Time::Delta();
		if (mousePos.y < moveRange)
			transform->translation += dirZ2 * moveSpeed * Time::Delta();

		FreeRange();

		viewMatrix = XMMatrixInverse(nullptr, transform->GetWorld());
	}
	break;
	default:
		break;
	}

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

		transform->translation = LERP(transform->translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(transform->translation, target->translation, V_UP);
	}
		break;

	case Camera::MODE2:
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			Vector3 dir = mousePos - oldPos;

			transform->rotation.y += dir.x * rotSpeed * Time::Delta();
			transform->rotation.x += dir.y * rotSpeed * Time::Delta();
		}
		oldPos = mousePos;

		destRotY = LERP(destRotY, transform->rotation.y, rotDamping * Time::Delta());
		destRotX = LERP(destRotX, transform->rotation.x, rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(destRotX, destRotY + rotY, 0.0f);

		Vector3 forward = V_FORWARD * rotMatrix;

		destination = target->GetGlobalPosition() + forward * distance;

		transform->translation = LERP(transform->translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(transform->translation, target->translation, V_UP);

		viewMatrix *= XMMatrixTranslation(0, -height, 0);
	}
	    break;
	case Camera::MODE3:
	{
		if (KEY_PRESS(VK_RBUTTON) && KEY_PRESS(VK_SHIFT))
		{
			Vector3 dir = mousePos - oldPos;

			transform->rotation.y += dir.x * rotSpeed * Time::Delta();
			transform->rotation.x += dir.y * rotSpeed * Time::Delta();
		}
		oldPos = mousePos;
		FixTarget(10.0f, 60.0f, 0.0f, XM_PI, Vector3(0.6f, 0.0f, 0.0f));

		destRotY = LERP(destRotY, transform->rotation.y, rotDamping * Time::Delta());
		destRotX = LERP(destRotX, transform->rotation.x, rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(destRotX + rotX, destRotY + rotY, 0.0f);

		Vector3 forward = V_FORWARD * rotMatrix;

		destination = target->GetGlobalPosition() + forward * distance;

		transform->translation = LERP(transform->translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(transform->translation, target->translation, V_UP);

		viewMatrix *= XMMatrixTranslation(0, -height, 0);
	}
	break;
	default:
		break;
	}

	//destination = target->translation - target->Backward() * distance + V_UP * height;

	//transform->translation = destination;

	//viewMatrix = XMMatrixLookAtLH(destination, target->translation, V_UP);

	////////////////////////////////////////////////////////////////////////////////////////

	//destination = target->translation - V_FORWARD * distance + V_UP * height;

	//transform->translation = destination;

	//viewMatrix = XMMatrixLookAtLH(destination, target->translation, V_UP);

	SetView();
}

void Camera::FixTarget(float height, float distance, float rotY, float rotX, Vector3 angle)
{
	this->height = height;
	this->distance = distance;
	this->rotY = rotY;
	this->rotX = rotX;
	transform->rotation = angle;
}

void Camera::FreeRange()
{

	if (distance > 20.0f)
		distance = 20.0f;
	if (distance < -20.0f)
		distance = -20.0f;

	if (transform->translation.y < 9.0f)
	{
		transform->translation.y = 9.5f;
		distance = 0.0f;
		return;
	}

	if (transform->translation.y > 34.0f)
	{
		transform->translation.y = 33.8f;
		distance = 0.0f;
		return;
	}

	//if(transform->translation.y < 9.0f)

	if (KEY_PRESS(VK_SHIFT))
	{
		transform->translation -= distance * transform->Forward() * Time::Delta();
	}
}

void Camera::SetView()
{
	transform->Update();

	//XMVECTOR   eyePos = transform->translation;
	//XMVECTOR focusPos = transform->translation + transform->Forward();
	//XMVECTOR upVector = transform->Up();

	//viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	viewBuffer->SetData(viewMatrix, transform->GetWorld());
	viewBuffer->SetVSBuffer(1);
}

void Camera::Save()
{
	BinaryWriter data(L"CameraData");

	data.WriteData(transform->scale);
	data.WriteData(transform->rotation);
	data.WriteData(transform->translation);
}

void Camera::Load()
{
	BinaryReader data(L"CameraData");

	if (!data.Succeeded())
		return;

	transform->scale = data.ReadVector3();
	transform->rotation = data.ReadVector3();
	transform->translation = data.ReadVector3();
}
