#pragma once
class MapTool : public Scene
{
public :
	MapTool();
	~MapTool();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;

private :
	shared_ptr<Player> _player;

	shared_ptr<Stool> _stool1;

	shared_ptr<Stool> _stool2;
};

