#include "Framework.h"
#include "SkyBox.h"

SkyBox::SkyBox(wstring file)
{
	sphere = new Sphere();
	sphere->GetMaterial()->SetShader(L"05SkyBox");
	sphere->SetLabel("Sky");

	rs = new RasterizerState();
	rs->FrontCounterClockWise(true);

	cubeMap = Texture::Get(file);
}

SkyBox::~SkyBox()
{
	delete sphere;
	delete rs;
}

void SkyBox::Render()
{
	cubeMap->PSSetShaderResources(10);
	sphere->Update();
	rs->SetState();

	StateManager::GetInstance()->DepthDisable();

	sphere->Render();

	RS->SetState();

	StateManager::GetInstance()->DepthEnable();
}

void SkyBox::PostRender()
{
	sphere->Debug();
}
