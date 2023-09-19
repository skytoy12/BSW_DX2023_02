#include "framework.h"
#include "SceneManager.h"

#include "TestScene/MapTool.h"
#include "TestScene/TestScene.h"
#include "TestScene/BossTestScene.h"

#include "GameScene/MainScene.h"
#include "GameScene/GameScene1.h"
#include "GameScene/GameScene2.h"
#include "GameScene/GameScene3.h"
#include "GameScene/BossScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	_scenes.push_back(make_shared<MainScene>());
	_scenes.push_back(make_shared<GameScene1>());
	_scenes.push_back(make_shared<GameScene2>());
	_scenes.push_back(make_shared<GameScene3>());
	_scenes.push_back(make_shared<BossScene>());
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

	_oldScene = _curScene;

	_scenes[_curScene]->End();
	++_curScene;
	_scenes[_curScene]->Init();

	if(_curScene == 1)
		_scenes[_curScene]->SetType(Scene::State::FIRST);
	
	if (_curScene == 2)
		_scenes[_curScene]->SetType(Scene::State::SECOND);

	if (_curScene == 3)
		_scenes[_curScene]->SetType(Scene::State::THIRD);

	if (_curScene == 4)
		_scenes[_curScene]->SetType(Scene::State::BOSS);
}

void SceneManager::PrevScene()
{
	if (_curScene <= 0 )
		return;

	_oldScene = _curScene;

	_scenes[_curScene]->End();
	--_curScene;
	_scenes[_curScene]->Init();
}

void SceneManager::SetScene(int number)
{
	if (number > _scenes.size() - 1 || number < 0)
		return;

	_oldScene = _curScene;

	_scenes[_curScene]->End();
	_curScene = number;
	_scenes[_curScene]->Init();
}
