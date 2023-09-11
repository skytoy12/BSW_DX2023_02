#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	terrainEditor = new TerrainEditor();
	terrainEditor->GetMaterial()-> SetDuffuseMap(L"Landscape/FieldStone_DM.tga");
	terrainEditor->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	terrainEditor->GetMaterial()->  SetNormalMap(L"Landscape/FieldStone_NM.tga");
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete terrainEditor;
}

void TerrainEditorScene::Update()
{
	terrainEditor->Update();
	if (KEY_DOWN(VK_LBUTTON))
		terrainEditor->Picking(&pickedPos);
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{
	terrainEditor->Render();
}

void TerrainEditorScene::PostRender()
{
	terrainEditor->Debug();

	ImGui::Text("PickedPos : %.1f, %.1f,%.1f", pickedPos.x, pickedPos.y, pickedPos.z);
}
