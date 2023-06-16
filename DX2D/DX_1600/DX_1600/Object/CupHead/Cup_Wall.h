#pragma once
class Cup_Wall
{
public :
	Cup_Wall();
	~Cup_Wall();

	void Update();
	void Render();

	shared_ptr<RectCollider> GetLeftWall() { return _leftWall; }
	shared_ptr<RectCollider> GetRightWall() { return _rightWall; }

private :
	shared_ptr<RectCollider> _leftWall;
	shared_ptr<RectCollider> _rightWall;
};

