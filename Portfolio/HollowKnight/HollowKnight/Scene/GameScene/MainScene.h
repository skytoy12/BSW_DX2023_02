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

	void UPSelect();
	void DOWNSelect();
	void Select();

	void Debug();

private :

	int _curPos = 0;

	shared_ptr<MainString> _title;

	shared_ptr<MainString> _start;
	shared_ptr<MainString> _load;
	shared_ptr<MainString> _finish;


	shared_ptr<SelectImage> _selectLeft;
	shared_ptr<SelectImage> _selectRight;
	shared_ptr<RectCollider> _select;


};

