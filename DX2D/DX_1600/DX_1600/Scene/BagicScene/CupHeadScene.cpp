#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Wall.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(CENTER);

	_boss = make_shared<Cup_Boss>();
	_boss->SetPosition(CENTER + Vector2(300, -130));

	_wall = make_shared<Cup_Wall>();

	_track = make_shared<Quad>(L"Resource/CupHead/Track.png");
	_transform = make_shared<Transform>();
	Vector2 trackSize = _track->GetQuadHalfSize();
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 75));

	Vector2 pos = CENTER;
	pos.y -= 350.0f;
	_col->GetTransform()->SetPosition(pos);

}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
	_boss->Update();

	_transform->Update();
	_col->Update();
	_wall->Update();

	if (_col->Block(_player->GetCollider()))
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
	_transform->SetBuffer(0);
	_track->Render();
	_col->Render();
	_wall->Render();

	_player->Render();
	_boss->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_boss->PostRender();
}
