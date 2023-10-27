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
	//scene = new ModelExportScene();
	//scene = new ModelAnimationScene();
	//scene = new CollisionScene();

	SCENE->Create("Grid", new GridScene());
	SCENE->Create("Collision", new CollisionScene());

	SCENE->Add("Grid");
	SCENE->Add("Collision");
}

MainGame::~MainGame()
{
	SceneManager::Delete();

	Release();
}

void MainGame::Update()
{
	SCENE->Update();

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

	SCENE->PreRender();

	Device::GetInstance()->Clear();

	Environment::GetInstance()->SetEnvironment();

	              SCENE->Render();
	Time::GetInstance()->Render();

	                SCENE->PostRender();
	     Camera::GetInstance()->Debug();
	Environment::GetInstance()->PostRender();

	ImGui::Checkbox("WireFrame", &isWireFrame);

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
