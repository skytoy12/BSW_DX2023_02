#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	//scene = new TutorialScene();
	//scene = new TextureScene();
	//scene = new RobotScene();
	//scene = new TerrainScene();
	//scene = new TerrainEditorScene();
	//scene = new SphereScene();
	scene = new ModelExportScene();
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

	if (isWireFrame)
	{
		RS->ChangeState(D3D11_FILL_WIREFRAME);
	}
	else
	{
		RS->ChangeState(D3D11_FILL_SOLID);
	}

	scene->PreRender();

	Device::GetInstance()->Clear();

	Environment::GetInstance()->SetEnvironment();

	              scene->Render();
	Time::GetInstance()->Render();

	                     scene->PostRender();
	     Camera::GetInstance()->PostRender();
	Environment::GetInstance()->PostRender();

	//ImGui::Checkbox("WireFrame", &isWireFrame);

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
