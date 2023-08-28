#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	//scene = new TutorialScene();
	scene = new TextureScene();
	//scene = new RobotScene();
}

MainGame::~MainGame()
{
	delete scene;

	Release();
}

void MainGame::Update()
{
	scene->Update();

	    Time::GetInstance()->Update();
	Keyboard::GetInstance()->Update();
}

void MainGame::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->PreRender();

	Device::GetInstance()->Clear();

	scene->Render();

	scene->PostRender();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
	     Device::GetInstance();
	Environment::GetInstance();
	   Keyboard::GetInstance();
	       Time::GetInstance();


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void MainGame::Release()
{
	     Device::Delete();
	     Shader::Delete();
	Environment::Delete();
	   Keyboard::Delete();
	       Time::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
