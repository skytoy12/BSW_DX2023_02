#pragma once
class Block
{
public :
	Block();
	~Block();

	void Update();
	void Render(HDC hdc);
private :
	shared_ptr<Collider> _rect;
};

