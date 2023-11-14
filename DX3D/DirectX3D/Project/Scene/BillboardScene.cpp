#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
	terrain = new Terrain(L"Landscape/Dirt2.png", L"HeightMap/HeightMap.png");

	for (UINT i = 0; i < 100; i++)
	{
		Vector2 size;

		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);

		Quad* tree = new Quad(size);
		tree->GetMaterial()->SetDiffuseMap(L"Landscape/Tree.png");
		tree->GetMaterial()->SetShader(L"Texture");

		Vector3 pos;
		pos.x = Random(0.0f, terrain->GetSize().x);
		pos.z = Random(0.0f, terrain->GetSize().y);

		pos.y = terrain->GetHeight(pos) + size.y * 0.5f;

		tree->translation = pos;

		trees.push_back(tree);
	}
}

BillboardScene::~BillboardScene()
{
	for (Quad* tree : trees)
		delete tree;
	trees.clear();

	delete terrain;
}

void BillboardScene::Update()
{
	for (Quad* tree : trees)
	{
		//tree->rotation = CAMERA->rotation;
		//tree->rotation.x = 0.0f;

		Vector3 dir = tree->GetGlobalPosition() - CAMERA->GetGlobalPosition();
		float angle = atan2f(dir.x, dir.z);
		tree->rotation.y = angle;
		tree->Update();
	}
	terrain->Update();
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
	terrain->Render();

	//StateManager::GetInstance()->AlphaBegin();
	StateManager::GetInstance()->AlphaToCoverageEnable();
	//StateManager::GetInstance()->DepthWriteMaskZero();
	for (Quad* tree : trees)
		tree->Render();
	StateManager::GetInstance()->AlphaEnd();
	//StateManager::GetInstance()->DepthEnable();
}

void BillboardScene::PostRender()
{
}
