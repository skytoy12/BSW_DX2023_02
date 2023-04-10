#pragma once
class CanonScene : public Scene
{
public :
	CanonScene();
	virtual ~CanonScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private :
	shared_ptr<Canon> _canon;
	shared_ptr<Canon> _canonEnemy;
};

