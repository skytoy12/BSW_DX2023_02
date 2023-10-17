#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";
	string name1 = "Y Bot";
	exporter = new ModelExporter(name);
	exporter->ExportModel();
	exporter->ExportClip("Hip Hop Dancing");

	modelAnimation = new ModelAnimation(name);
	modelAnimation->ReadClip("Hip Hop Dancing");
	modelAnimation->CreateTexture();

	//model = new Model(name);

	//model = new ModelBSW();
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;

	delete modelAnimation;

	//delete model;
}

void ModelExportScene::Update()
{
	modelAnimation->Update();
	//model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	modelAnimation->Render();
	//model->Render();
}

void ModelExportScene::PostRender()
{
	//model->GetReader()->Debug();
}
