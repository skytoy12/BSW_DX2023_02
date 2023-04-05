#pragma once
class LineScene : public Scene
{
public :
	LineScene();
	virtual ~LineScene();

	virtual void Updata() override;
	virtual void Render(HDC hdc) override;
private :	
	shared_ptr<Line> _lineFloor;
	shared_ptr<Line> _lineMouse;
	shared_ptr<Line> _lineShadow;
};

