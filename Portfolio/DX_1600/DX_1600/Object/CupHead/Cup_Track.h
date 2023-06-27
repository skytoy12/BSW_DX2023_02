#pragma once
class Cup_Track
{
public :
	Cup_Track(Vector2 pos);
	~Cup_Track();
	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }
	Vector2 GetPosition() { return _col->GetTransform()->GetWorldPosition(); }

	shared_ptr<Collider> GetCollider() { return _col; }

	Vector2 GetTrackSize() { return _trackHalfSize; }

	bool _isActive = true;

private :
	shared_ptr<Collider> _col;

	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	Vector2 _trackHalfSize;
};

