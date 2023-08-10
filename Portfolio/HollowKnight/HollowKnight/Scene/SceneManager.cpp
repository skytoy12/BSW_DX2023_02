#include "framework.h"
#include "SceneManager.h"

#include "BagicScene/MapTool.h"
#include "BagicScene/TestScene.h"
#include "BagicScene/BossTestScene.h"


SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{

	_scenes.push_back(make_shared<TestScene>());
	_scenes.push_back(make_shared<BossTestScene>());
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	_scenes[_curScene]->Update();
}

void SceneManager::Render()
{
	_scenes[_curScene]->Render();
}

void SceneManager::PostRender()
{
	_scenes[_curScene]->PostRender();

	if (ImGui::Button("NextScene", { 30, 30 }))
		NextScene();

	if (ImGui::Button("PrevScene", { 30, 30 }))
		PrevScene();

	ImGui::SliderInt("SetScene", (int*)&_test, 0, 2);

	if (ImGui::Button("SetSceneNumber", { 30, 30 }))
		SetScene(_test);
}

void SceneManager::NextScene()
{
	if (_curScene >= _scenes.size() - 1)
		return;

	_scenes[_curScene]->End();
	++_curScene;
	_scenes[_curScene]->Init();

}

void SceneManager::PrevScene()
{
	if (_curScene <= 0 )
		return;

	_scenes[_curScene]->End();
	--_curScene;
	_scenes[_curScene]->Init();
}

void SceneManager::SetScene(int number)
{
	if (number > _scenes.size() - 1 || number < 0)
		return;

	_scenes[_curScene]->End();
	_curScene = number;
	_scenes[_curScene]->Init();
}
