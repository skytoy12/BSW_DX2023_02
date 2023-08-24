#pragma once


#define V_RIGHT    vector3(+1.0f, +0.0f, +0.0f)
#define V_LEFT     vector3(-1.0f, +0.0f, +0.0f)
#define V_UP       vector3(+0.0f, +1.0f, +0.0f)
#define V_DOWN     vector3(+0.0f, -1.0f, +0.0f)
#define V_FORWARD  vector3(+0.0f, +0.0f, +1.0f)
#define V_BACKWARD vector3(+0.0f, +0.0f, -1.0f)


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

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

