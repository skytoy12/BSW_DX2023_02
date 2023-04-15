#pragma once
class ArkanoidScene : public Scene
{
public :
	ArkanoidScene();
	~ArkanoidScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private :
	shared_ptr<ArkanoidBlocks> _arkanoid;
	shared_ptr<Frame> _arkanoidFrame;
	shared_ptr<Bar> _bar;
};

