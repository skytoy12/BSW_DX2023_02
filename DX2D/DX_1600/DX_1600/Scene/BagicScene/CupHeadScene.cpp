#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Boss_2phase.h"
#include "../../Object/CupHead/Cup_Wall.h"
#include "../../Object/CupHead/Cup_Track.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0,0));

	_boss = make_shared<Cup_Boss>();
	_boss->SetPosition(Vector2(0, 0));

	_2phase = make_shared<Cup_Boss_2phase>();
	_2phase->SetPosition(Vector2(0, -200));

	_wall = make_shared<Cup_Wall>();

	_track = make_shared<Cup_Track>();

	CAMERA->SetTarget(_player->GetTransform());
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
	_boss->Update();
	_2phase->Update();
	_track->Update();
	_wall->Update();

	if (_2phase->GetCollider()->GetPos().x > _player->GetCollider()->GetPos().x)
		_2phase->SetLeft();
	else
		_2phase->SetRight();

	if (_boss->_isAlive == false && _2phase->_isDead == false)
	{
		_2phase->_isAlive = true;
	}

	if (_wall->GetUpWall()->Block(_2phase->GetCollider()) && _player->_isDead == false)
	{
		_2phase->Fire(_player->GetCollider()->GetPos());
	}

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

	if (_player->_isActive == true)
	{
		if (_boss->GetCollider()->IsCollision(_player->GetCollider()) && _boss->_isAlive == true && _player->_isHitted == false)
		{
			_player->_isHitted = true;
			_player->Damaged(1);
			_player->SetType(Cup_Player::State::HIT);
		}

		if (_2phase->isCollision_Bullets(_player->GetCollider()) && _player->_isHitted == false)
		{
			_player->_isHitted = true;
			_player->Damaged(1);
			_player->SetType(Cup_Player::State::HIT);
		}
	}


}

void CupHeadScene::Render()
{
	_2phase->Render();
	_track->Render();

	_wall->Render();

	_player->Render();
	_boss->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_boss->PostRender();
	_2phase->PostRender();
}
