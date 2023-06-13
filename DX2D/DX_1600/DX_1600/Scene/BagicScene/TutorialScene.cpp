#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{

	_quad = make_shared<Quad>(L"Resource/SUN.png");
	_quad->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));
	_transform = make_shared<Transform>();



	_transform->SetPosition(CENTER);

	_filterBuffer = make_shared<FilterBuffer>();

	_filterBuffer->_data.imageSize = _quad->GetImageSize();
	_filterBuffer->_data.radialCenter = Vector2(0.5f, 0.5f);

	
}

TutorialScene::~TutorialScene()
{
}


void TutorialScene::Update()
{
	_transform->Update();
	_filterBuffer->Update();
}

void TutorialScene::Render()
{
	_transform->SetBuffer(0);
	_filterBuffer->SetPSBuffer(0);
	_quad->Render();
}

void TutorialScene::PostRender()
{
	ImGui::SliderInt("Selected", &_filterBuffer->_data.selected, 0, 10);
	ImGui::SliderInt("value1", &_filterBuffer->_data.Value1, 1, 300);
	ImGui::SliderInt("value2", &_filterBuffer->_data.Value2, 0, 300);
	ImGui::SliderInt("value3", &_filterBuffer->_data.Value3, 0, 300);
}
