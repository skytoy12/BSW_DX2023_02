#include "framework.h"
#include "BossHead.h"

using namespace tinyxml2;

BossHead::BossHead()
{
	_transform = make_shared<Transform>();
	_col = make_shared<CircleCollider>(70);

	_transform->SetParent(_col->GetTransform());

	CreateAction(L"Resource/Monster/Boss/BossHead.png", "Resource/Monster/Boss/BossHead.xml", "BossHead",
	Vector2((float)(117 * 1.3), (float)(118 * 1.3)), Action::Type::LOOP);

	CreateAction(L"Resource/Monster/Boss/BossHeadHit.png", "Resource/Monster/Boss/BossHeadHit.xml", "BossHeadHit",
	Vector2((float)(120 * 1.3), (float)(138 * 1.3)), Action::Type::LOOP);
}

BossHead::~BossHead()
{
}

void BossHead::Update()
{
	if (_isActive == false)
		return;

	_col->Update();
	_transform->Update();

	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

}

void BossHead::Render()
{
	if (_isActive == false)
		return;

	_transform->SetBuffer(0);

	_sprites[_curstate]->SetCurClip(_actions[_curstate]->GetCurClip());
	_sprites[_curstate]->Render();

	_col->Render();
}

void BossHead::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

	sprite->SetPS(ADD_PS(L"Shader/MonsterPS.hlsl"));
	_actions.push_back(action);
	_sprites.push_back(sprite);
}
