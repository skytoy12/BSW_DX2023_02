#pragma once


#define V_RIGHT    Vector3(+1.0f, +0.0f, +0.0f)
#define V_LEFT     Vector3(-1.0f, +0.0f, +0.0f)
#define V_UP       Vector3(+0.0f, +1.0f, +0.0f)
#define V_DOWN     Vector3(+0.0f, -1.0f, +0.0f)
#define V_FORWARD  Vector3(+0.0f, +0.0f, +1.0f)
#define V_BACKWARD Vector3(+0.0f, +0.0f, -1.0f)


struct Vector3
{
	Vector3()
	{
	}

	Vector3(float x, float y, float z)
		:x(x), y(y), z(z)
	{
	}

	Vector3(XMFLOAT3 value)
		: x(value.x), y(value.y), z(value.z)
	{
	}

	Vector3(XMVECTOR vector)
	{
		x = XMVectorGetX(vector);
		y = XMVectorGetY(vector);
		z = XMVectorGetZ(vector);
	}

	operator XMVECTOR()
	{
		//XMVECTOR vector;
		//vector = XMVectorSet(z, y, z, 0.0f);

		//return vector;

		return XMVectorSet(x, y, z, 0.0f);
	}

	operator XMFLOAT3()
	{
		return XMFLOAT3(z, y, z);
	}

	float Length() { return XMVectorGetX(XMVector3Length(*this)); }

	void Normalize() { *this = XMVector3Normalize(*this); } // 원본을 수정하는 것

	Vector3 GetNormalized() { return XMVector3Normalize(*this); } // 원본을 수정하지 않고 값만 가져오는 것

	static Vector3 Cross(Vector3 v1, Vector3 v2)
	{
		return XMVector3Cross(v1, v2);
	}

	static float Dot(Vector3 v1, Vector3 v2)
	{
		return XMVectorGetX(XMVector3Dot(v1, v2));
	}

	Vector3 operator+ (const Vector3& other)
	{
		return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3 operator- (const Vector3& other) 
	{
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	void operator+= (const Vector3& other)
	{
		this->x += other.x; 
		this->y += other.y; 
		this->z += other.z; 
	
	}
	void operator-= (const Vector3& other) 
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
	}

	Vector3 operator* (const float& value) 
	{
		return Vector3(this->x * value, this->y * value, this->z * value);
	}

	Vector3 operator/ (const float& value)
	{
		return Vector3(this->x / value, this->y / value, this->z / value);
	}

	void operator*= (const float& value) 
	{
		this->x *= value; 
		this->y *= value; 
		this->z *= value; 
	}

	void operator/= (const float& value) 
	{
		this->x /= value;
		this->y /= value;
		this->z /= value;
	}

	Vector3 operator*(const Matrix& value)
	{
		/// TODO : coord버전 구분하기

		return XMVector3TransformNormal(*this, value);
	}

	float operator[](const UINT& index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return 0.0f;
		}
	}

	bool operator==(const Vector3& other)
	{
		return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

