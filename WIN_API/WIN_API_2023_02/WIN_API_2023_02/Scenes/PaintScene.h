#pragma once
class PaintScene : public Scene
{
public :
	PaintScene();
	virtual ~PaintScene();

	// Scene을(를) 통해 상속됨
	virtual void Updata() override;
	virtual void Render(HDC hdc) override;
private :
	shared_ptr<CircleCollider> _circle;
	float _speed = 10.0f;
	shared_ptr<RectengleCollider> _rectengle;
};

