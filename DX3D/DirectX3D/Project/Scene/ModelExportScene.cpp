#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("Knight D Pelegrini");
	exporter->ExportModel();

	reader = new ModelReader("Knight D Pelegrini");
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
	delete reader;
}

void ModelExportScene::Update()
{
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
}

void ModelExportScene::PostRender()
{
}
