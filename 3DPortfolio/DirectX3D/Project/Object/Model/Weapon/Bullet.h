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

	void SetRay(Vector3 origin, Vector3 direction);
	void SetRay(Ray ray) { bullet = ray; }

	void SetDestination(Vector3 pos) { bullet.direction = pos; }
	void SetOrigin(Vector3 pos) { bullet.origin = pos; }

	void SetTarget(Transform* target) { this->target = target; }

	void SetColor(float r, float g, float b) { material->GetBuffer()->data.diffuse = { r, g, b, 1.0f }; }

	void SetRange(float value) { range = value; }

	Vector3 GetOrigin() { return bullet.origin; }

private:
	Material* material;
	Mesh* mesh;

	Ray bullet;


	vector<VertexType> vertices;
	vector<UINT>        indices;

	Transform* target = nullptr;

	float range = 50.0f;
};



