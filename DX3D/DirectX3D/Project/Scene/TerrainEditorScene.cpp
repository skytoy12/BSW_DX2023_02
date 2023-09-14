#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	terrainEditor = new TerrainEditor();
	terrainEditor->GetMaterial()-> SetDuffuseMap(L"Landscape/FieldStone_DM.tga");
	terrainEditor->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	terrainEditor->GetMaterial()->  SetNormalMap(L"Landscape/FieldStone_NM.tga");

	RawData();
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
	terrainEditor->GetMaterial()->SelectMap();

	ImGui::Text("PickedPos : %.1f, %.1f,%.1f", pickedPos.x, pickedPos.y, pickedPos.z);
}

void TerrainEditorScene::RawData()
{
	ComputeShader* shader = Shader::GetCS(L"ByteAddress");

	struct Output
	{
		UINT groupID[3];
		UINT groupThreadID[3];
		UINT dispatchThreadID[3];
		UINT groupIndex;
	};

	UINT size = 10 * 8 * 3 * 2;

	Output* output = new Output[size];

	RawBuffer* buffer = new RawBuffer(nullptr, sizeof(Output) * size);

	ID3D11UnorderedAccessView* uav = buffer->GetUAV();

	shader->SetShader();

	DC->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);

	DC->Dispatch(2, 1, 1);

	buffer->Copy(output, sizeof(Output) * size);

	FILE* file;
	fopen_s(&file, "_TextData/RawTest.csv", "w");

	for (UINT i = 0; i < size; i++)
	{
		fprintf
		(
			file,
			"%d, %d,%d,%d, %d,%d,%d, %d,%d,%d, %d\n",
			i,
			output[i].groupID[0],
			output[i].groupID[1],
			output[i].groupID[2],
			output[i].groupThreadID[0],
			output[i].groupThreadID[1],
			output[i].groupThreadID[2],
			output[i].dispatchThreadID[0],
			output[i].dispatchThreadID[1],
			output[i].dispatchThreadID[2],
			output[i].groupIndex
		);
	}

	fclose(file);

	delete buffer;

	delete output;
}
