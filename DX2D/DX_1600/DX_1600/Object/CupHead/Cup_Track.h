#pragma once
class Cup_Track
{
public :
	Cup_Track();
	~Cup_Track();
	void Update();
	void Render();

	shared_ptr<Collider> GetCollider() { return _col; }

	Vector2 GetTrackSize() { return _trackHalfSize; }

private :
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _col;
	shared_ptr<Transform> _transform;

	Vector2 _trackHalfSize;
};

