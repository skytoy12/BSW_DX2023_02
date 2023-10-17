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
	//ModelBSW* model;

	//Model* model;
	ModelAnimator* modelAnimator;
};



