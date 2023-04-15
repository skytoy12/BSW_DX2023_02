#pragma once
class Bar
{
public :
	Bar();
	~Bar();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();
	shared_ptr<class Ball> GetBallByBar() { return _ball; }
	

private :
	shared_ptr<Collider> _arkanoidBar;
	HBRUSH _brush;
	float _speed = 5.0f;
	shared_ptr<class Ball> _ball;

};

