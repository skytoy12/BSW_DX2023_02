#pragma once
class HPFrame
{
public:
	HPFrame();
	~HPFrame();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};



