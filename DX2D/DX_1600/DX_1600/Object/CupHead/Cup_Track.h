#pragma once
class Cup_Track
{
public :
	Cup_Track();
	~Cup_Track();
	void Update();
	void Render();

	shared_ptr<Collider> GetCollider() { return _col; }

private :
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _col;
	shared_ptr<Transform> _transform;
};

