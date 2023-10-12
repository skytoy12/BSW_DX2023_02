#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";
	exporter = new ModelExporter(name);
	//exporter->ExportModel();
	exporter->ExportClip("Hip Hop Dancing");

	model = new Model(name);

	//model = new ModelBSW();
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;


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
