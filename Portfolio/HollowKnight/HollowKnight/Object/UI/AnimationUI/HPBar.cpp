#include "framework.h"
#include "HPBar.h"

using namespace tinyxml2;

HPBar::HPBar()
{
	_transform = make_shared<Transform>();

	CreateAction(L"Resource/UI/HP/FullHP.png", "Resource/UI/HP/FullHP.xml", "FullHP",
	Vector2(228.0f * 0.1f, 305.0f * 0.1f), Action::Type::LOOP);

	CreateAction(L"Resource/UI/HP/BrokenHP.png", "Resource/UI/HP/BrokenHP.xml", "BrokenHP",
	Vector2(228.0f * 0.1f, 305.0f * 0.1f), Action::Type::LOOP);
}

HPBar::~HPBar()
{
}

void HPBar::Update()
{
	_transform->Update();
	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	if (_curstate == FULL)
		_actions[BROKEN]->Reset();
}

void HPBar::PostRender()
{
	if (_curstate == NONE)
		return;
	_transform->SetBuffer(0);
	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();
}

void HPBar::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmmlPath.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;


	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	action->Update();
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	sprite->SetPS(ADD_PS(L"Shader/NonRedPS.hlsl"));
	sprite->Update();
	_actions.push_back(action);
	_sprites.push_back(sprite);
}
