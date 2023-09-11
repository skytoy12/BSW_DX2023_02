#pragma once
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

private :
	shared_ptr<MainString> _title;


};

