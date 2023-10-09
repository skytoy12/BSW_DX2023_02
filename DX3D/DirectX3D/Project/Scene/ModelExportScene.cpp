#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	//exporter = new ModelExporter("Knight D Pelegrini");
	//exporter->ExportModel();

	//reader = new ModelReader("Knight D Pelegrini");

	model = new Model();
}

ModelExportScene::~ModelExportScene()
{
	//delete exporter;
	//delete reader;

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
}
