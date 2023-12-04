#pragma once
class Bullet : public Transform

{
	typedef Vertex VertexType;
public:
	Bullet();
	~Bullet();

	void CreateMesh();

	void Update();
	void Render();
	void Debug();


	void SetDirection(Vector3 pos) { bullet.direction = pos; }
	void SetDestination(Vector3 pos) { destination = pos; }
	void SetOrigin(Vector3 pos) { bullet.origin = pos; }

	void SetTarget(Transform* target) { this->target = target; }

	void SetColor(float r, float g, float b) { material->GetBuffer()->data.diffuse = { r, g, b, 1.0f }; }

	void SetRange(float value) { range = value; }
	void SetIsActive(bool value) { bulletActive = value; }

	Vector3 GetOrigin() { return bullet.origin; }
	Vector3 GetDestination() { return destination; }
	float GetRange() { return range; }
	bool GetIsActive() { return bulletActive; }
private:
	Material* material;
	Mesh* mesh;

	Ray bullet;


	vector<VertexType> vertices;
	vector<UINT>        indices;

	Transform* target = nullptr;

	Vector3 destination;

	float range = 50.0f;
	float activeTime = 0.0f;
	bool bulletActive = false;
};



