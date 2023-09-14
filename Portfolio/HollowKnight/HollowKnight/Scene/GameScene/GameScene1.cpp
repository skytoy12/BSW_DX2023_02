#include "framework.h"
#include "GameScene1.h"

GameScene1::GameScene1()
{
	_player = make_shared<Player>();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>(Vector2(50, 50));
		_walls.push_back(wall);
	}

	for (auto wall : _walls)
	{
		wall->SetTarget(_player);
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

	for (auto wall : _walls)
	{
		wall->Update();
	}


	if (KEY_UP(VK_UP))
		_colNum += 1;

	if (KEY_UP(VK_DOWN))
		_colNum -= 1;
}

void GameScene1::Render()
{
	_player->Render();

	for (auto wall : _walls)
	{
		wall->Render();
	}

}

void GameScene1::PostRender()
{
	_player->PostRender();

	ImGui::SliderFloat("Scale.x", (float*)&_scale, 0.1f, 2.0f);
	ImGui::Text("colNum : %d", _colNum);
}

void GameScene1::PreRender()
{

}

void GameScene1::CreateMap()
{
	_walls[0]->SetPosition(Vector2(- 250, + 230));
	_walls[1]->SetPosition(Vector2(+ 250, + 230));
	_walls[2]->SetPosition(Vector2(+   0, - 700));
	_walls[3]->SetPosition(Vector2(-1400, - 750));
	_walls[4]->SetPosition(Vector2(- 872, - 965));
	_walls[5]->SetPosition(Vector2(- 350, -1290));

	_walls[0]->SetScale(Vector2( 2, 10));
	_walls[1]->SetScale(Vector2( 2, 10));
	_walls[2]->SetScale(Vector2(20,  3));
	_walls[3]->SetScale(Vector2(20,  4));
	_walls[4]->SetScale(Vector2( 3,  8));
	_walls[5]->SetScale(Vector2(20,  4));
}

void GameScene1::MoveCol()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_walls[_colNum]->SetPosition(W_MOUSE_POS);
		}
	}

}
