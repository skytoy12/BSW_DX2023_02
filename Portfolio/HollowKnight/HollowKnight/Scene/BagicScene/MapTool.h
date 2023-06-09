#pragma once
class MapTool : public Scene
{
public :
	MapTool();
	~MapTool();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private :
	shared_ptr<CircleCollider> _collider;
};

