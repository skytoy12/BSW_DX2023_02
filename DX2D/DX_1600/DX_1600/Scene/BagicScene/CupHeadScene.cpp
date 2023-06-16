#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Wall.h"
#include "../../Object/CupHead/Cup_Track.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(CENTER);

	_boss = make_shared<Cup_Boss>();
	_boss->SetPosition(CENTER + Vector2(300, -130));

	_wall = make_shared<Cup_Wall>();

	_track = make_shared<Cup_Track>();


}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
	_boss->Update();
	_track->Update();
	_wall->Update();

	if (_track->GetCollider()->Block(_player->GetCollider()))
	{
		if (_player->_isJump == true)
			_player->SetType(Cup_Player::State::IDLE);
		_player->_isJump = false;
	}

	if (_boss->GetCollider()->IsCollision(_wall->GetLeftWall()))
	{
		_boss->_isWallCrash = true;
		_boss->GetCollider()->GetTransform()->AddVector2(Vector2(100, 0));
	}

	if (_boss->GetCollider()->IsCollision(_wall->GetRightWall()))
	{
		_boss->_isWallCrash = true;
		_boss->GetCollider()->GetTransform()->AddVector2(Vector2(-100, 0));
	}

	if (_boss->_isAlive == true)
	{
		if (_player->isCollision_Bullets(_boss->GetCollider()))
		{
			_boss->Damage(1);
		}
	}


}

void CupHeadScene::Render()
{
	_track->Render();

	_wall->Render();

	_player->Render();
	_boss->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_boss->PostRender();
}
