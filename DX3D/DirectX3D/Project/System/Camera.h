#pragma once


class Camera : public Singleton<Camera>
{
	friend class Singleton;

public :
	enum Mode
	{
		MODE1,
		MODE2
	};
private:
	Camera();
	~Camera();
public:
	void Update();

	void Debug();

	Transform* GetTransform() { return transform; }

	Ray ScreenPointToRay(Vector3 screenPos);

	void SetTarget(Transform* target) { this->target = target; }

private:
	void   FreeMode();
	void TargetMode(Mode mode = MODE1);

	void SetView();

	void Save();
	void Load();

private:
	Transform* transform;
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
};