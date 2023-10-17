#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";
	string name1 = "Y Bot";
	exporter = new ModelExporter(name);
	exporter->ExportModel();
	exporter->ExportClip("Hip Hop Dancing");

	modelAnimator = new ModelAnimator(name);
	modelAnimator->ReadClip("hip hop dancing");
	modelAnimator->CreateTexture();



	//model = new Model(name);

	//model = new ModelBSW();
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;


	delete modelAnimator;

	//delete model;
}

void ModelExportScene::Update()
{
	modelAnimator->Update();
	//model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	modelAnimator->Render();
	//model->Render();
}

void ModelExportScene::PostRender()
{
	//model->GetReader()->Debug();
}
