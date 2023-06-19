#include "framework.h"
#include "Program.h"

#include "../Scene/BagicScene/TutorialScene.h"
#include "../Scene/BagicScene/SolorSystem.h"
#include "../Scene/BagicScene/DungreedScene.h"
#include "../Scene/BagicScene/DungreedBossScene.h"
#include "../Scene/BagicScene/ColliderScene.h"
#include "../Scene/BagicScene/SpriteScene.h"
#include "../Scene/BagicScene/ActionScene.h"
#include "../Scene/BagicScene/CupHeadScene.h"
#include "../Scene/BagicScene/EffectScene.h"

Program::Program()
{
	srand(unsigned int(time(nullptr)));
	_curScene = make_shared<CupHeadScene>();


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

	_curScene->Collider_Update();
	_curScene->Update();

	EffectManager::GetInstance()->Update();
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

	CAMERA->PostRender();
	_curScene->Render();
	EffectManager::GetInstance()->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());

	_curScene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
