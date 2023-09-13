#include "framework.h"
#include "GameScene1.h"

GameScene1::GameScene1()
{
	_player = make_shared<Player>();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(Vector2(50, 50));
		_cols.push_back(col);
	}
	for (auto col : _cols)
	{
		col->SetPosition(Vector2(0,0));
	}
	CAMERA->SetTarget(nullptr);
	//CAMERA->SetTarget(_player->GetTransform());

	CreateMap();

	_player->SetPosition(Vector2(0, 1000));
}

GameScene1::~GameScene1()
{

}

void GameScene1::Update()
{
	_player->Update();

	CAMERA->SetScale(Vector2(_scale, _scale));
	MoveCol();
	for (auto col : _cols)
	{
		col->Update();
	}

	for (auto col : _cols)
	{
		if (col->Block(_player->GetCollider()))
			_player->SetIsJump(false);
	}

	if (KEY_UP(VK_UP))
		_colNum += 1;

	if (KEY_UP(VK_DOWN))
		_colNum -= 1;
}

void GameScene1::Render()
{
	_player->Render();

	for (auto col : _cols)
	{
		col->Render();
	}
}

void GameScene1::PostRender()
{
	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	ImGui::Text("colNum : %d", _colNum);
}

void GameScene1::PreRender()
{

}

void GameScene1::CreateMap()
{
	_cols[0]->SetPosition(Vector2(-250, +230));
	_cols[1]->SetPosition(Vector2(+250, +230));
	_cols[2]->SetPosition(Vector2(+000, -700));
	_cols[3]->SetPosition(Vector2(-1300, -750));
	_cols[4]->SetPosition(Vector2(-772, -965));

	_cols[0]->SetScale(Vector2(2, 10));
	_cols[1]->SetScale(Vector2(2, 10));
	_cols[2]->SetScale(Vector2(20, 5));
	_cols[3]->SetScale(Vector2(20, 6));
	_cols[4]->SetScale(Vector2(3, 8));
}

void GameScene1::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_cols[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}

}
