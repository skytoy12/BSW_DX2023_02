#pragma once
class PaintScene : public Scene
{
public :
	PaintScene();
	virtual ~PaintScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Updata() override;
	virtual void Render(HDC hdc) override;
private :
	shared_ptr<CircleCollider> _circle;
	float _speed = 10.0f;
};

