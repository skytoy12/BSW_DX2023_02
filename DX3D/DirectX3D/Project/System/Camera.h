#pragma once


class Camera : public Transform
{
public :
	enum Mode
	{
		MODE1,
		MODE2
	};

public:
	Camera();
	~Camera();
	void Update();

	void Debug();


	Ray ScreenPointToRay(Vector3 screenPos);

	Vector3 WorldToScreenPoint(Vector3 worldPos);

	void SetTarget(Transform* target) { this->target = target; }

	ViewBuffer* GetViewBuffer() { return viewBuffer; }

	bool ContainPoint(Vector3 point);
	bool ContainSphere(Vector3 center, float radius);

private:
	void   FreeMode();
	void TargetMode(Mode mode = MODE1);

	void SetView();

	void Save();
	void Load();

	void CalculateFrustum();

private:
	float moveSpeed = 30.0f;
	float  rotSpeed = 30.0f;

	ViewBuffer* viewBuffer;
	Matrix        viewMatrix;

	Vector3 oldPos;
	Vector3 cameraDir;

	Transform* target;

	float distance = 20.0f;
	float height   = 10.0f;

	Vector3 destination;
	Vector3 focusOffset;

	float rotY     = 0.0f;
	float destRotY = 0.0f;
	float destRotX = 0.0f;

	float moveDamping = 5.0f;
	float  rotDamping = 5.0f;

	XMVECTOR planes[6];
	float a, b, c, d;
};