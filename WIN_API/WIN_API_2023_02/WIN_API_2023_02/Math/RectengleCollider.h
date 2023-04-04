#pragma once
class RectengleCollider
{
public :
	RectengleCollider(float left, float top, float right, float bottom);
	~RectengleCollider();
	
	void Updata();
	void Render(HDC hdc);

	void MoveRecVT(const float& value);
	void MoveRecHR(const float& value);

private :
	float _left;
	float _top;
	float _bottom;
	float _right;
};

