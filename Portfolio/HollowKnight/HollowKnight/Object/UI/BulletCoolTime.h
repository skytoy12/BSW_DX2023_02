#pragma once
class BulletCoolTime
{
public :
	BulletCoolTime();
	~BulletCoolTime();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private :
	shared_ptr<Collider> _col;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<RatioBuffer> _ratioBuffer;
};

