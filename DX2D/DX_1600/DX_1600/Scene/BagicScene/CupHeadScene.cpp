#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Boss_2phase.h"
#include "../../Object/CupHead/Cup_Wall.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Cup_Track2.h"

CupHeadScene::CupHeadScene()
{
#pragma region CupHead
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0,0));

	_boss = make_shared<Cup_Boss>();
	_boss->SetPosition(Vector2(0, 0));

	_2phase = make_shared<Cup_Boss_2phase>();
	_2phase->SetPosition(Vector2(0, -200));

	_wall = make_shared<Cup_Wall>();

	_track = make_shared<Cup_Track>(CENTER);
	_track2 = make_shared<Cup_Track2>();

	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", srv->GetImageSize() + Vector2(500, 0));
	_button->SetEvent(std::bind(&CupHeadScene::Load, this));


	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(Vector2(-_track->GetTrackSize().x, _track->GetCollider()->GetPos().y));
	CAMERA->SetRightTop(Vector2(_track2->GetCollider()->GetPos().x + _track2->GetTrackSize().x, 1000.0f));

	Load();
#pragma endregion

#pragma region RTV
	_rtv = make_shared<RenderTarget>();
	_rtvQuad = make_shared<Quad>(Vector2(WIN_WIDTH, WIN_HEIGHT));
	shared_ptr<SRV> rtvsrv = make_shared<SRV>(_rtv->GetSRV());
	_rtvQuad->SetSRV(rtvsrv);
	_rtvQuad->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));

	_rtvTransform = make_shared<Transform>();
	_filterbuffer = make_shared<FilterBuffer>();
	
#pragma endregion
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Init()
{
	Load();
}

void CupHeadScene::End()
{
	// CupHead 총알회수 함수...
}

void CupHeadScene::Update()
{
	_player->Update();
	_boss->Update();
	_2phase->Update();
	_track->Update();
	_track2->Update();
	_wall->Update();
	_button->Update();


	if(_player->GetCollider()->GetPos().x > _track->GetCollider()->GetPos().x + _track->GetTrackSize().x)
		CAMERA->SetLeftBottom(Vector2(-_track->GetTrackSize().x, _track2->GetCollider()->GetPos().y));
	if (_player->GetCollider()->GetPos().x < _track->GetCollider()->GetPos().x + _track->GetTrackSize().x)
		CAMERA->SetLeftBottom(Vector2(-_track->GetTrackSize().x, _track->GetCollider()->GetPos().y));

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
			_player->SetState(Cup_Player::State::IDLE);
		_player->_isJump = false;
	}

	if (_track2->GetCollider()->Block(_player->GetCollider()) && _player->GetCollider()->GetPos().x > _track2->GetCollider()->GetPos().x - _track2->GetTrackSize().x
		 && _player->GetCollider()->GetPos().x < _track2->GetCollider()->GetPos().x + _track2->GetTrackSize().x)
	{
		if (_player->_isJump == true)
			_player->SetState(Cup_Player::State::IDLE);
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
		if (_boss->GetCollider()->IsCollision(_player->GetCollider()) && _boss->_isAlive == true)
		{
			//if (_player->_isInvincibility == true)
			//	return;
			_player->SetType(Cup_Player::State::HIT);
			_player->_isHitted = true;
			_player->_isInvincibility = true;
			_player->Damaged(1);
		}

		if (_2phase->isCollision_Bullets(_player->GetCollider()) && _player->_isHitted == false)
		{
			//if (_player->_isInvincibility == true)
			//	return;
			_player->SetType(Cup_Player::State::HIT);
			_player->_isHitted = true;
			_player->_isInvincibility = true;
			_player->Damaged(1);
		}
	}


}

void CupHeadScene::Render()
{
	_rtvTransform->SetBuffer(0);
	_filterbuffer->SetPSBuffer(0);
	_rtvQuad->Render();
}

void CupHeadScene::PreRender()
{
	_rtv->Set();

	_2phase->Render();
	_track->Render();
	_track2->Render();

	_wall->Render();

	_boss->Render();
	_player->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_boss->PostRender();
	_2phase->PostRender();
	_button->PostRender();

	if(ImGui::Button("TargetON", ImVec2(100, 50)))
	{
		CAMERA->SetTarget(_player->GetTransform());
	}

	if (ImGui::Button("TargetOff", ImVec2(100, 50)))
	{
		CAMERA->SetTarget(nullptr);
	}

	if (ImGui::Button("Save", ImVec2(100, 50)))
	{
		Save();
	}

	if (ImGui::Button("Load", ImVec2(100, 50)))
	{
		Load();
	}

}

void CupHeadScene::Save()
{
	BinaryWriter writer = BinaryWriter(L"Save/test.test");
	writer.Int(1);

	Vector2 playerPos = _player->GetCollider()->GetTransform()->GetWorldPosition();

	writer.String("PlayerPos");
	writer.Byte(&playerPos, sizeof(Vector2));
}

void CupHeadScene::Load()
{
	BinaryReader reader = BinaryReader(L"Save/test.test");
	int temp = reader.Int();

	string str = reader.String();
	assert(str == "PlayerPos");

	Vector2 playerPos;
	Vector2* ptr = &playerPos;
	reader.Byte((void**)&ptr, sizeof(Vector2));

	_player->SetPosition(playerPos);

}
