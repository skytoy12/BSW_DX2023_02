#include "Framework.h"
#include "DeferredRenderScene.h"

DeferredRenderScene::DeferredRenderScene()
{
	CreateObjects();
	gBuffer = new GeometryBuffer();

	material = new Material(L"12DeferredRender");

	vector<UINT> vertices = { 0, 1, 2, 3 };

	vertexBuffer = new VertexBuffer(vertices);
}

DeferredRenderScene::~DeferredRenderScene()
{
	delete floor;
	delete groot;
	delete bunny;
	delete sphere;

	delete gBuffer;

	delete material;
	delete vertexBuffer;
}

void DeferredRenderScene::Update()
{
	floor -> Update();
	groot -> Update();
	bunny -> Update();
	sphere-> Update();
}

void DeferredRenderScene::PreRender()
{
	gBuffer->SetMultiRenderTarget();

	floor->Render();
	groot->Render();
	bunny->Render();
	sphere->Render();
}

void DeferredRenderScene::Render()
{
	vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	gBuffer->SetSRVs();
	material->SetMaterial();

	//Camera::GetInstance()->GetViewBuffer()->SetPSBuffer(1);
	//Environment::GetInstance()->GetPersBuffer()->SetPSBuffer(2);

	DC->Draw(4, 0);
}

void DeferredRenderScene::PostRender()
{
	gBuffer->PostRender();
}

void DeferredRenderScene::CreateObjects()
{
	floor = new Quad();
	floor->SetLabel("Floor");

	floor->rotation.x = XM_PIDIV2;
	floor->translation.y = 1.0f;
	floor->scale *= 100.0f;
	floor->GetMaterial()->SetShader(L"12GeometryBuffer");

	//floor->scale.x *= WIN_WIDTH * 0.5f;
	//floor->scale.y *= WIN_HEIGHT * 0.5f;

	//floor->translation.x = WIN_WIDTH * 0.25f;
	//floor->translation.y = WIN_HEIGHT * 0.25f;


	groot = new Groot();
	groot->GetReader()->SetShader(L"12GeometryBuffer");

	bunny = new Model("StanfordBunny");
	bunny->SetLabel("Bunny");
	bunny->scale *= 0.05f;
	bunny->translation = { -30, 12, 0 };
	bunny->GetReader()->SetShader(L"12GeometryBuffer");

	sphere = new Sphere();
	sphere->scale *= 5.0f;
	sphere->translation = { 30, 20, 0 };
	sphere->GetMaterial()->SetDiffuseMap(L"LandScape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetNormalMap(L"LandScape/FieldStone_NM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"LandScape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetShader(L"12GeometryBuffer");
	sphere->SetLabel("Sphere");
}
