#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	//scene = new TutorialScene();
	//scene = new TextureScene();
	//scene = new RobotScene();
	scene = new TerrainScene();
	//scene = new SphereScene();
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
	  Camera::GetInstance()->Update();
}

void MainGame::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->PreRender();

	Device::GetInstance()->Clear();

	Environment::GetInstance()->SetEnvironment();

	scene->Render();

	scene->PostRender();

	     Camera::GetInstance()->PostRender();
	Environment::GetInstance()->PostRender();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
   StateManager::GetInstance();
	Environment::GetInstance();
	   Keyboard::GetInstance();
	     Device::GetInstance();
	       Time::GetInstance();


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void MainGame::Release()
{
	       Time::Delete();
	     Device::Delete();
	     Shader::Delete();
	   Keyboard::Delete();
	Environment::Delete();
   StateManager::Delete();
         Camera::Delete();
		Texture::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
