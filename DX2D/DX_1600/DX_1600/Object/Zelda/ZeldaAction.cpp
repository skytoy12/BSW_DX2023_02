#include "framework.h"
#include "ZeldaAction.h"

ZeldaAction::ZeldaAction()
{
	CreateAction();
	Vector2 size = ADD_SRV(L"Resource/spritezelda.png")->GetImageSize();
	size.x /= 10;
	size.y /= 8;
	_sprite = make_shared<Sprite>(L"Resource/spritezelda.png", Vector2(10, 8), size);
	_transform = make_shared<Transform>();

	_transform->SetPosition(CENTER);

	// Listner 패턴, Observer 패턴, 구독자 패턴
	_forwordAction->SetEndEvent(std::bind(&ZeldaAction::EndEvent, this));

	_action = &_forwordAction;
}

ZeldaAction::~ZeldaAction()
{
}

void ZeldaAction::Update()
{
	Select();

	_sprite->Update();
	_transform->Update();
	(*_action)->Update();
}

void ZeldaAction::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurframe((*_action)->GetCurClip());
	_sprite->Render();
}

void ZeldaAction::PostRender()
{
	if (_isEnd)
		ImGui::Text("EndEvent!!!");
}

void ZeldaAction::Select()
{
	if (KEY_PRESS('A'))
	{
		_leftAction->Play();
		_action = &_leftAction;
	}

	if (KEY_PRESS('D'))
	{
		_rightAction->Play();
		_action = &_rightAction;
	}

	if (KEY_PRESS('W'))
	{
		_backAction->Play();
		_action = &_backAction;
	}

	if (KEY_PRESS('S'))
	{
		_forwordAction->Play();
		_action = &_forwordAction;
	}
}

void ZeldaAction::CreateAction()
{
	// 앞으로 걸어다니는 액션
	vector<Action::Clip> forwordClips;
	vector<Action::Clip> backClips;
	vector<Action::Clip> rightClips;
	vector<Action::Clip> leftClips;
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/spritezelda.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = { 10, 8 };
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;



		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, 4 * h, w, h, srv);
			forwordClips.push_back(clip1);
		}

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, 5 * h, w, h, srv);
			leftClips.push_back(clip1);
		}

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, 6 * h, w, h, srv);
			backClips.push_back(clip1);
		}

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(i * w, 7 * h, w, h, srv);
			rightClips.push_back(clip1);
		}
	}

	_forwordAction = make_shared<Action>(forwordClips, "RUN_F", Action::Type::LOOP);
	_backAction = make_shared<Action>(backClips, "RUN_B", Action::Type::LOOP);
	_leftAction = make_shared<Action>(leftClips, "RUN_L", Action::Type::LOOP);
	_rightAction = make_shared<Action>(rightClips, "RUN_R", Action::Type::LOOP);
	
	_forwordAction->Play();
}
