#pragma once
class Transform
{
public:
	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return world; }

	void SetParent(Transform* parent) { this->parent = parent; }

public:
	Vector3 scale       = { 1.0f, 1.0f, 1.0f };
	Vector3 rotation    = { 0.0f, 0.0f, 0.0f };
	Vector3 translation = { 0.0f, 0.0f, 0.0f };

protected :
	Matrix world;

	Vector3 pivot = {};

	Transform* parent = nullptr;
};


