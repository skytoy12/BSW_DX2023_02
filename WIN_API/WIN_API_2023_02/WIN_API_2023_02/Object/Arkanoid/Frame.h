#pragma once
class Frame
{
public :
	Frame();
	~Frame();

	void Update();
	void Render(HDC hdc);

private :
	shared_ptr<Collider> _arkanoidFrame;
	HBRUSH _brush;
};

