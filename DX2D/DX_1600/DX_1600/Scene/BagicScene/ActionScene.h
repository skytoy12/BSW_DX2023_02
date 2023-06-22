#pragma once
class ActionScene : public Scene
{
public :
	ActionScene();
	~ActionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;



private :
	shared_ptr<class ZeldaAction> _zelda;

};

