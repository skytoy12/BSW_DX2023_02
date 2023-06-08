#include "framework.h"
#include "ZeldaAction.h"
#include "ZeldaPotion.h"

ZeldaAction::ZeldaAction()
{
	CreateAction();
	Vector2 size = ADD_SRV(L"Resource/spritezelda.png")->GetImageSize();
	size.x /= 10;
	size.y /= 8;
	_sprite = make_shared<Sprite>(L"Resource/spritezelda.png", Vector2(10, 8), size * 0.7f);
	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(size * 0.7f);

	_transform->SetParent(_collider->GetTransform());
	_collider->SetPosition(CENTER);

	for (int i = 0; i < 4; i++)
	{
		_actions[i]->SetEndEvent(std::bind(&ZeldaAction::EndEvent, this));
	}
	_state = ZeldaAction::IDLE_F;
	
	_potion1 = make_shared<ZeldaPotion>(Vector2(4, 0), Vector2(RandomNum(0, WIN_WIDTH), RandomNum(0, WIN_HEIGHT)));
	_potion2 = make_shared<ZeldaPotion>(Vector2(5, 0), Vector2(RandomNum(0, WIN_WIDTH), RandomNum(0, WIN_HEIGHT)));
	_potion3 = make_shared<ZeldaPotion>(Vector2(2, 2), Vector2(RandomNum(0, WIN_WIDTH), RandomNum(0, WIN_HEIGHT)));
	_potion4 = make_shared<ZeldaPotion>(Vector2(4, 2), Vector2(RandomNum(0, WIN_WIDTH), RandomNum(0, WIN_HEIGHT)));

}

ZeldaAction::~ZeldaAction()
{
}

void ZeldaAction::Collider_Update()
{
	_collider->Update();

	_potion1->Collider_Update();
	_potion2->Collider_Update();
	_potion3->Collider_Update();
	_potion4->Collider_Update();
}

void ZeldaAction::Update()
{
	Select();
	_sprite->Update();
	_transform->Update();
	_actions[_state]->Update();

	_potion1->Update();
	_potion2->Update();
	_potion3->Update();
	_potion4->Update();

	GetPotion(_potion1);
	GetPotion(_potion2);
	GetPotion(_potion3);
	GetPotion(_potion4);
}

void ZeldaAction::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurFrame(_actions[_state]->GetCurClip());
	_sprite->Render();
	_collider->Render();

	_potion1->Render();
	_potion2->Render();
	_potion3->Render();
	_potion4->Render();
}

void ZeldaAction::PostRender()
{
	if (_isEnd)
		ImGui::Text("EndEvent!!!");
	ImGui::Text("HP : %d", _hp);
}

void ZeldaAction::GetPotion(shared_ptr<class ZeldaPotion> other)
{
	if (other->_isActive == false)
		return;

	if (_collider->IsCollision(other->GetCollider()))
	{
		other->SetIsActive(false);
		Recovery(100);
	}
}


void ZeldaAction::Select()
{
	if (KEY_UP('S'))
	{
		_state = ZeldaAction::IDLE_F;
	}

	if (KEY_UP('W'))
	{
		_state = ZeldaAction::IDLE_B;
	}

	if (KEY_UP('D'))
	{
		_state = ZeldaAction::IDLE_R;
	}

	if (KEY_UP('A'))
	{
		_state = ZeldaAction::IDLE_L;

	}

	if (KEY_PRESS('S'))
	{
		_state = ZeldaAction::RUN_F;
		Vector2 movePos = Vector2(0.0f, -500.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('W'))
	{
		_state = ZeldaAction::RUN_B;
		Vector2 movePos = Vector2(0.0f, 500.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		_state = ZeldaAction::RUN_R;
		Vector2 movePos = Vector2(500.0f, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('A'))
	{
		_state = ZeldaAction::RUN_L;
		Vector2 movePos = Vector2(-500.0f, 0.0f) * DELTA_TIME;
		Move(movePos);
	}
}

void ZeldaAction::CreateAction()
{
	// 앞으로 걸어다니는 액션
	vector<Action::Clip> Clips;
	
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/spritezelda.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = { 10, 8 };
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;

		CreateIdle(h, w, 0, "IDLE_F", srv, Action::Type::LOOP, 3);
		CreateIdle(h, w, 2, "IDLE_B", srv, Action::Type::LOOP, 1);
		CreateIdle(h, w, 3, "IDLE_R", srv, Action::Type::LOOP, 3);
		CreateIdle(h, w, 1, "IDLE_L", srv, Action::Type::LOOP, 3);
		CreateRun(h, w, 4, "RUN_F", srv, Action::Type::LOOP);
		CreateRun(h, w, 6, "RUN_B", srv, Action::Type::LOOP);
		CreateRun(h, w, 7, "RUN_R", srv, Action::Type::LOOP);
		CreateRun(h, w, 5, "RUN_L", srv, Action::Type::LOOP);


	}

	
}

void ZeldaAction::CreateRun(float h, float w, int Y, string name, shared_ptr<SRV> srv, Action::Type type)
{
	vector<Action::Clip> Clips;
	{

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, Y * h, w, h, srv);
			Clips.push_back(clip1);
		}

	}
	shared_ptr<Action> action = make_shared<Action>(Clips, name, type);
	action->Play();
	_actions.push_back(action);
}

void ZeldaAction::CreateIdle(float h, float w, int Y, string name, shared_ptr<SRV> srv, Action::Type type, int num)
{
	vector<Action::Clip> Clips;
	{

		for (int i = 0; i < num; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, Y * h, w, h, srv);
			Clips.push_back(clip1);
		}

	}
	shared_ptr<Action> action = make_shared<Action>(Clips, name, type);
	action->Play();
	_actions.push_back(action);
}
