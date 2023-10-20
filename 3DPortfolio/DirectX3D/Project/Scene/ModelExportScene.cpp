#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";
	string name1 = "Y Bot";

	exporter = new ModelExporter(name);
	//exporter->ExportModel();
	//exporter->ExportClip("Old Man Idle");
	//exporter->ExportClip("Running");

	modelAnimator = new ModelAnimator(name);
	modelAnimator->ReadClip("hip hop dancing");
	modelAnimator->ReadClip("Old Man Idle");
	modelAnimator->ReadClip("Running");
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

	if (KEY_DOWN('1'))
		modelAnimator->PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		modelAnimator->PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		modelAnimator->PlayClip(2, speed, takeTime);

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

	ImGui::SliderFloat(   "Speed",    &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f,  1.0f);
}
