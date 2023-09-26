#include "framework.h"
#include "Program.h"


Program::Program()
{
	srand(unsigned int(time(nullptr)));


	Timer::GetInstance()->SetLockFPS(60.0);
}

Program::~Program()
{
}

void Program::Update()
{
	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	Sound::GetInstance()->Update();
	CAMERA->Update();


	SCENE->Update();

	EffectManager::GetInstance()->Update();

	if (KEY_DOWN(VK_F1))
	{
		Collider::_isDebug = !Collider::_isDebug;
	}
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CAMERA->SetCameraBuffer();
	CAMERA->SetProjectionBuffer();


	ALPHA->SetState();

	Font::GetInstance()->GetDC()->BeginDraw();

	SCENE->Render();
	EffectManager::GetInstance()->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	ImGui::Text("W_MOUSEPOS : { %.0f , %.0f }", W_MOUSE_POS.x, W_MOUSE_POS.y);
	ImGui::Text("S_MOUSEPOS : { %.0f , %.0f }", S_MOUSE_POS.x, S_MOUSE_POS.y);
	ImGui::Text("MOUSEPOS : { %.0f , %.0f }", MOUSE_POS.x, MOUSE_POS.y);
	ImGui::Text("_curScene : %d", SCENE->GetCurScene());
	ImGui::Text("_oldScene : %d", SCENE->GetOldScene());

	CAMERA->SetUICameraBuffer();
	CAMERA->PostRender();
	SCENE->PostRender();

	ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::GetInstance()->GetDC()->EndDraw();

	Device::GetInstance()->Present();
}
