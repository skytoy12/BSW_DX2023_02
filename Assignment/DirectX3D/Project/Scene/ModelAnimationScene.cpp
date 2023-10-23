#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	groot = new Groot();

	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap.png");

	//CAMERA->SetParent(groot);
	//CAMERA->scale *= 5;
	//
	//CAMERA->translation = Vector3(0.0f, 7.6f, 14.0f);

}

ModelAnimationScene::~ModelAnimationScene()
{
	delete groot;
	delete terrain;
}

void ModelAnimationScene::Update()
{
	groot->Update();
	terrain->Update();

	if (terrain->ModelPicking(&pickedPos, groot->translation + Vector3(0.0f, 5000.0f, 0.0f)))
		groot->translation.y = pickedPos.y;

	//cameraPos = groot->translation + Vector3(0.0f, 7.6f, 14.0f);
	//CAMERA->translation = cameraPos;

	//cameraRot = groot->rotation;
	//CAMERA->rotation = cameraRot + Vector3(0.25f, 3.3f, 0.0f);
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	groot->Render();
	terrain->Render();
}

void ModelAnimationScene::PostRender()
{
	groot->Debug();
	ImGui::Text("pickedPos : %.3f, %.3f, %.3f", pickedPos.x, pickedPos.y, pickedPos.z);

	ImGui::SliderFloat("CAMERAx", &cameraRot.x, -10.0f, 10.0f);
	ImGui::SliderFloat("CAMERAy", &cameraRot.y, -10.0f, 10.0f);
	ImGui::SliderFloat("CAMERAz", &cameraRot.z, -10.0f, 10.0f);
}
