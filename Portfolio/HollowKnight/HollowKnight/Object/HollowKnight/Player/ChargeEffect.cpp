#include "framework.h"
#include "ChargeEffect.h"

using namespace tinyxml2;

ChargeEffect::ChargeEffect()
{
	_transform = make_shared<Transform>();
	CreateAction(L"Resource/Effect/ChargeEffect.png", "Resource/Effect/ChargeEffect.xml", "ChargeEffect", Vector2(317, 295), Action::Type::LOOP);
}

ChargeEffect::~ChargeEffect()
{
}

void ChargeEffect::Update()
{
	if (_isActive == false)
		return;



	_transform->Update();
	_actions[_state]->Update();
	_sprites[_state]->Update();



	if (!_isActive)
	{
		_state = START;
		_actions[_state]->Reset();
	}
}

void ChargeEffect::Render()
{
	if (_isActive == false)
		return;
	_transform->SetBuffer(0);

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();

}

void ChargeEffect::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	sprite->SetPS(ADD_PS(L"Shader/NonRedPS.hlsl"));
	_actions.push_back(action);
	_sprites.push_back(sprite);
}
