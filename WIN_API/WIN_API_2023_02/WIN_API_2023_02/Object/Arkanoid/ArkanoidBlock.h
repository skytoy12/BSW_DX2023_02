#pragma once
class ArkanoidBlock
{
public:
	ArkanoidBlock();
	~ArkanoidBlock();

	void Update();
	void Render(HDC hdc);
private:
	shared_ptr<Collider> _rect;
};

