#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Y Bot";
	//exporter = new ModelExporter(name);
	//exporter->ExportModel();
	//model = new ModelBSW();

	model = new Model(name);
}

ModelExportScene::~ModelExportScene()
{
	//delete exporter;


	delete model;
}

void ModelExportScene::Update()
{
	model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	model->Render();
}

void ModelExportScene::PostRender()
{
	model->GetReader()->Debug();
}
