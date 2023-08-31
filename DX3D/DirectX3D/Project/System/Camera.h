#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton;
private:
	Camera();
	~Camera();
public:
	void Update();

	void PostRender();
private:
	void   FreeMode();
	void TargetMode();

	void SetView();

private:
	Transform* transform;
	float moveSpeed = 20.0f;
	float rotSpeed = 7.5f;

	MatrixBuffer* viewBuffer;
	Matrix        viewMatrix;

	Vector3 oldPos;
};

