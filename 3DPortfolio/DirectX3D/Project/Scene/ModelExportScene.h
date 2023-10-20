#pragma once
class ModelExportScene : public Scene
{
public:
	ModelExportScene();
	~ModelExportScene();


	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;
private:
	ModelExporter* exporter;

	//Model* model;
	ModelAnimator* modelAnimator;

	float speed = 1.0f;
	float takeTime = 0.2f;
};



