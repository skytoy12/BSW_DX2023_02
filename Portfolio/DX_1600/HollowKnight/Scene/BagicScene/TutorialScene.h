#pragma once
class TutorialScene : public Scene
{
public :
	TutorialScene();
	virtual ~TutorialScene();


	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private :
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<FilterBuffer> _filterBuffer;

	float _angle = 0.0f;
};

