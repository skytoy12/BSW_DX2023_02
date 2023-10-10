#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Fieldstone_DM.tga", L"LandScape/Fieldstone_SM.tga", L"LandScape/Fieldstone_NM.tga", L"HeightMap/HeightMap.png");
	robot = new Robot();
}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete robot;
}


void TerrainScene::Update()
{
	terrain->Update();
	robot->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		terrain->Picking(&pickedPos);
		Vector3 Pos = pickedPos + Vector3(0, 5, 0);
		robot->SetPosition(Pos);
	}

}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();
	robot->Render();
}

void TerrainScene::PostRender()
{
	terrain->GetMaterial()->Debug();

	ImGui::Text("PickedPos : %.1f, %.1f,%.1f", pickedPos.x, pickedPos.y, pickedPos.z);
}
