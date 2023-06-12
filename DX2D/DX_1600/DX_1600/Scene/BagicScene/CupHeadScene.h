#pragma once
class CupHeadScene : public Scene
{
public :
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private :
	shared_ptr<class Cup_Player> _player;
	shared_ptr<Transform> _transform;

	shared_ptr<class Cup_Boss> _boss;
	shared_ptr<Quad> _track;
	shared_ptr<Collider> _col;
};

