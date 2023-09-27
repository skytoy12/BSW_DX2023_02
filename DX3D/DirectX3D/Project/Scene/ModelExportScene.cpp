#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	exporter = new ModelExporter("_modelData/FBX/" + name + ".fbx");
	exporter->ExportMaterial(name);
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
