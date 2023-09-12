#include "framework.h"
#include "SoulOrb.h"

using namespace tinyxml2;

SoulOrb::SoulOrb()
{
	_transform = make_shared<Transform>();
	CreateAction(L"Resource/UI/HP/SoulOrb.png", "Resource/UI/HP/SoulOrb.xml", "SoulOrb",
	Vector2(130, 125), Action::Type::LOOP);
	_action->SetSpeed(0.5f);
}

SoulOrb::~SoulOrb()
{
}

void SoulOrb::Update()
{
	_transform->Update();
	_action->Update();
	_sprite->Update();
}

void SoulOrb::PostRender()
{
	_transform->SetBuffer(0);
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Render();
}

void SoulOrb::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

	_action = make_shared<Action>(clips, actionName, type);
	_action->Play();
	_action->SetEndEvent(event);
	_action->Update();
	_sprite = make_shared<Sprite>(srvPath, size);

	_sprite->SetPS(ADD_PS(L"Shader/NonRedPS.hlsl"));
	_sprite->Update();
}
