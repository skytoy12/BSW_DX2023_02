#pragma once

struct Ray
{
	Vector3 origin;
	Vector3 direction;
};

class Camera : public Singleton<Camera>
{
	friend class Singleton;
private:
	Camera();
	~Camera();
public:
	void Update();

	void Debug();

	Transform* GetTransform() { return transform; }

	Ray ScreenPointToRay(Vector3 screenPos);
private:
	void   FreeMode();
	void TargetMode();

	void SetView();

	void Save();
	void Load();

private:
	Transform* transform;
	float moveSpeed = 10.0f;
	float rotSpeed = 1.5f;

	ViewBuffer* viewBuffer;
	Matrix        viewMatrix;

	Vector3 oldPos;
	Vector3 cameraDir;
};

