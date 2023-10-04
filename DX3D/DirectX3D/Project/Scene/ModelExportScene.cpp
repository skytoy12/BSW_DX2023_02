#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("Knight D Pelegrini");
	exporter->ExportMaterial();
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
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
