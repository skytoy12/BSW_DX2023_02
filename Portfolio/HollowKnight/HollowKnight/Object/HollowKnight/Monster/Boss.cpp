#include "framework.h"
#include "Boss.h"

Boss::Boss()
{
	_isLeft = true;
	_gravityCol = make_shared<RectCollider>(Vector2(20, 260));
	_col = make_shared<CircleCollider>(130);
	_transform->SetParent(_gravityCol->GetTransform());
	_col->SetParent(_gravityCol->GetTransform());
	_col->SetPosition(Vector2(0, -10));
	LocationFix();
	CreateAction(L"Resource/Monster/Boss/BossIdle.png", "Resource/Monster/Boss/BossIdle.xml", "Idle", Vector2(620, 393), Action::Type::LOOP);
	_actions[IDLE]->SetSpeed(0.2f);
	CreateAction(L"Resource/Monster/Boss/BossRunReady.png", "Resource/Monster/Boss/BossRunReady.xml", "RunReady", Vector2(571, 375), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossRun.png", "Resource/Monster/Boss/BossRun.xml", "Run", Vector2(617, 481), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossTurn.png", "Resource/Monster/Boss/BossTurn.xml", "Turn", Vector2(545, 388), Action::Type::END, std::bind(&Boss::TurnEvent, this));
	_actions[TURN]->SetSpeed(0.15f);
	CreateAction(L"Resource/Monster/Boss/BossAttackReady.png", "Resource/Monster/Boss/BossAttackReady.xml", "AttackReady", Vector2(578, 399), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossAttack.png", "Resource/Monster/Boss/BossAttack.xml", "Attack", Vector2(701, 587), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossAttackFinish.png", "Resource/Monster/Boss/BossAttackFinish.xml", "AttackFinish", Vector2(647, 572), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossJumpReady.png", "Resource/Monster/Boss/BossJumpReady.xml", "JumpReady", Vector2(605, 381), Action::Type::LOOP);
	CreateAction(L"Resource/Monster/Boss/BossJump.png", "Resource/Monster/Boss/BossJump.xml", "Jump", Vector2(598, 335), Action::Type::LOOP);
	_gravityCol->SetPosition(Vector2(500, 0));
}

Boss::~Boss()
{
}

void Boss::Update()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	Gravity(_gravityCol);
	_col->Update();
	_gravityCol->Update();
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_turnCoolTime += DELTA_TIME;

	LocationFix(); // collider에 transform을 맞춰주는 함수
	DirFix();
	UnActiveIDle();
	Turn(); 
	//_col->SetPosition(_location);
}

void Boss::Render()
{
	if (_target.expired() == true)
		return;
	if (_isAlive == false)
		return;

	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();
	_col->Render();
	_gravityCol->Render();
}

void Boss::PostRender()
{
	ImGui::SliderFloat("Location.x", (float*)&_location.x, -100.0f, 200.0f);
	ImGui::SliderFloat("Location.y", (float*)&_location.y, -100.0f, 200.0f);
	ImGui::SliderInt("CurState", (int*)&_curstate, 0, 8);
	ImGui::Text("_isLeft : %d", _isLeft);
	ImGui::Text("_isTurn : %d", _isTurn);
}

void Boss::Attack()
{
}

void Boss::SetState(State_Boss type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
}

void Boss::SetAndResetState(State_Boss type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
	_actions[_oldstate]->Reset();
}

void Boss::SetAndPlayState(State_Boss type)
{
	_oldstate = _curstate;
	_curstate = type;
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();
	_actions[_curstate]->Play();
}

void Boss::Turn()
{
	if (_isTurn == true)
		return;
	if (_isAttack == true)
		return;
	if (_isJump == true)
		return;
	if (_turnCoolTime < 0.4f)
		return;

	_actions[TURN]->Reset();
	_actions[TURN]->Play();

	if (_isLeft == true)
	{
		if (_gravityCol->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x < 0)
		{
			_isTurn = true;
			_actions[TURN]->Update();
			if (_isLeft == false)
				SetLeft();
			else
				SetRight();
			SetState(TURN);
			LocationFix();
		}
		return;
	}

	if (_isLeft == false)
	{
		if (_gravityCol->GetTransform()->GetWorldPosition().x - _target.lock()->GetWorldPosition().x > 0)
		{
			_isTurn = true;
			_actions[TURN]->Update();
			if (_isLeft == false)
				SetLeft();
			else
				SetRight();
			SetState(TURN);
			LocationFix();
		}
		return;
	}
}

void Boss::UnActiveIDle()
{
	if (_isJump == false && _isAttack == false && _isTurn == false)
	{
		SetState(IDLE);
		LocationFix();
	}

}	   

void Boss::TurnEvent()
{
	_actions[IDLE]->Update();
	_isTurn = false;
	_turnCoolTime = 0.0f;
}

void Boss::LocationFix()
{
	if (_curstate == IDLE)
	{
		_transform->SetPosition(Vector2(61, 63));
	}

	if (_curstate == RUNREADY)
	{
		_transform->SetPosition(Vector2(112, 55));
	}

	if (_curstate == RUN)
	{
		_transform->SetPosition(Vector2(112, 106));
	}

	if (_curstate == TURN)
	{
		_transform->SetPosition(Vector2(0, 58));
	}

	if (_curstate == ATTACKREADY)
	{
		_transform->SetPosition(Vector2(116, 48));
	}

	if (_curstate == ATTACK)
	{
		_transform->SetPosition(Vector2(-74, 138));
	}

	if (_curstate == ATTACKFINISH)
	{
		_transform->SetPosition(Vector2(0, 146));
	}

	if (_curstate == JUMPREADY)
	{
		_transform->SetPosition(Vector2(53, 56));
	}

	if (_curstate == JUMP)
	{
		_transform->SetPosition(Vector2(123, 37));
	}
}

void Boss::DirFix()
{
	if (_isJump == false && _dir.Length() != 0)
	{
		_dir = Vector2(_target.lock()->GetWorldPosition().x, 0.0f) - Vector2(_gravityCol->GetTransform()->GetWorldPosition().x, 0.0f);
		_dir = _dir.NomalVector2();
	}
}

void Boss::LandAttackPattern()
{
}

void Boss::JumpAttackPattern()
{
}

void Boss::AfterGroggyPattern()
{
}

void Boss::SetLeft()
{
	_actions[_curstate]->Update();
	_gravityCol->SetScale(Vector2(1, 1));
	_isLeft = true;
}

void Boss::SetRight()
{
	_actions[_curstate]->Update();
	_gravityCol->SetScale(Vector2(-1, 1));
	_isLeft = false;
}
