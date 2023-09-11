#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_title = make_shared<MainString>(L"Resource/UI/Title.png", Vector2(1185.0f * 0.5f, 412.0f * 0.5f));
	_start = make_shared<MainString>(L"Resource/UI/TestString.png",  Vector2(754.0f * 0.2f, 84.0f * 0.2f));
	_load = make_shared<MainString>(L"Resource/UI/TestString.png",   Vector2(754.0f * 0.2f, 84.0f * 0.2f));
	_finish = make_shared<MainString>(L"Resource/UI/TestString.png", Vector2(754.0f * 0.2f, 84.0f * 0.2f));

	_select = make_shared<RectCollider>(Vector2(200, 50));
	_selectLeft = make_shared<SelectImage>();
	_selectRight = make_shared<SelectImage>();

	_start->SetPosition(Vector2(0.0f, -100.0f));
	_load->SetPosition(Vector2(0.0f, -175.0f));
	_finish->SetPosition(Vector2(0.0f, -250.0f));

	_select->SetPosition(Vector2(0.0f, -100.0f));

	_selectLeft->GetTransform()->SetParent(_select->GetTransform());
	_selectRight->GetTransform()->SetParent(_select->GetTransform());

	_selectLeft->SetPosition(Vector2(-100, 0));
	_selectRight->SetPosition(Vector2(+100, 0));

	_title->SetPosition(Vector2(0,200));
	_selectRight->SetScale(Vector2(-1, 1));
}

MainScene::~MainScene()
{
}

void MainScene::Update()
{
	_title ->Update();
	_start ->Update();
	_load  ->Update();
	_finish->Update();

	_select->Update();
	_selectLeft->Update();
	_selectRight->Update();

	Select();

	UPSelect();
	DOWNSelect();
}

void MainScene::Render()
{
}

void MainScene::PostRender()
{
	_title ->PostRender();
	_start ->PostRender();
	_load  ->PostRender();
	_finish->PostRender();

	_select->Render();
	_selectLeft->PostRender();
	_selectRight->PostRender();


	Debug();
}

void MainScene::PreRender()
{
}

void MainScene::UPSelect()
{
	if (KEY_DOWN(VK_DOWN))
	{
		if (_curPos == 0)
		{
			_select->SetPosition(_load->GetPos());
			_curPos = 1;
			return;
		}

		if (_curPos == 1)
		{
			_select->SetPosition(_finish->GetPos());
			_curPos = 2;
			return;
		}

		if (_curPos == 2)
		{
			_select->SetPosition(_start->GetPos());
			_curPos = 0;
			return;
		}
	}
}

void MainScene::DOWNSelect()
{
	if (KEY_DOWN(VK_UP))
	{
		if (_curPos == 0)
		{
			_select->SetPosition(_finish->GetPos());
			_curPos = 2;
			return;
		}

		if (_curPos == 1)
		{
			_select->SetPosition(_start->GetPos());
			_curPos = 0;
			return;
		}

		if (_curPos == 2)
		{
			_select->SetPosition(_load->GetPos());
			_curPos = 1;
			return;
		}
	}
}

void MainScene::Select()
{
	if (KEY_PRESS(VK_RETURN))
	{
		if (_select->IsCollision(RECT(_start->GetCollider())))
		{
			SCENE->NextScene();
		}
	}

	if (KEY_PRESS(VK_RETURN))
	{
		if (_select->IsCollision(RECT(_finish->GetCollider())))
		{
			DestroyWindow(hWnd);
		}
	}
}

void MainScene::Debug()
{
	ImGui::Text("_curPos : %d", _curPos);

	ImGui::Text("_curPosVector : %.1f, %.1f", _select->GetTransform()->GetWorldPosition().x, _select->GetTransform()->GetWorldPosition().y);

}
