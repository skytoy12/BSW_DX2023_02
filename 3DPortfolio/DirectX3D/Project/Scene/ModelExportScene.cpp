#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";
	string name1 = "Y Bot";
	string name2 = "Groot";
	string name3 = "Dwarven_Axe";
	string name4 = "EliteFederationSoldier";
	string name5 = "PoliceZombie";
	string name6 = "shot gun triangulated";
	string name7 = "ShotGun";


	exporter = new ModelExporter(name6);
	exporter->ExportModel();
	//exporter->ExportClip("Rifle/Rifle Idle");
	//exporter->ExportClip("Rifle/Rifle Run");
	//exporter->ExportClip("Rifle/Rifle Walk");
	//exporter->ExportClip("Idle/Breathing Idle");
	//exporter->ExportClip("Zombie Attack");
	//exporter->ExportClip("Idle/Walking");
	//exporter->ExportClip("Sad Idle");
	//exporter->ExportClip("Standing Melee Attack 360 High");



	model = new Model(name6);
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
