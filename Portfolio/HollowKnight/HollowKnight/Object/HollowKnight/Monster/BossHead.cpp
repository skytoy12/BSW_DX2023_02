#include "framework.h"
#include "BossHead.h"

using namespace tinyxml2;

BossHead::BossHead()
{
	_transform = make_shared<Transform>();
	_col = make_shared<CircleCollider>(70);
	_monsterBuffer = make_shared<MonsterBuffer>();

	_transform->SetParent(_col->GetTransform());

	CreateAction(L"Resource/Monster/Boss/BossHead.png", "Resource/Monster/Boss/BossHead.xml", "BossHead",
	Vector2((float)(117 * 1.3), (float)(118 * 1.3)), Action::Type::LOOP);

	CreateAction(L"Resource/Monster/Boss/BossHeadHit.png", "Resource/Monster/Boss/BossHeadHit.xml", "BossHeadHit",
	Vector2((float)(120 * 1.4), (float)(138 * 1.4)), Action::Type::LOOP);

	CreateAction(L"Resource/Monster/Boss/LastHead.png", "Resource/Monster/Boss/LastHead.xml", "LastHead",
	Vector2((float)(271), (float)(190)), Action::Type::END);

	_monsterBuffer->_data.state = 1;
}

BossHead::~BossHead()
{
}

void BossHead::Update()
{
	if (_isActive == false)
		return;

	if (_isUnbeatableH == false)
		SetRGB(0.0f, 0.0f, 0.0f);

	if (_lastHead == true)
		_curstate = LASTHEAD;

	_col->Update();
	_transform->Update();
	_monsterBuffer->Update();

	_actions[_curstate]->Update();
	_sprites[_curstate]->Update();

	UnbeatableToIdleH();

}

void BossHead::Render()
{
	if (_isActive == false)
		return;

	_transform->SetBuffer(0);
	_monsterBuffer->SetPSBuffer(1);

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

void BossHead::SetRGB(float R, float G, float B)
{
	_monsterBuffer->_data.R = R;
	_monsterBuffer->_data.G = G;
	_monsterBuffer->_data.B = B;
}

void BossHead::hurt()
{
	if (_isUnbeatableH == true)
		return;
	_hp -= 1;
	_curstate = HIT;
	SetRGB(0.2f, 0.2f, 0.2f);
	_col->SetPosition(Vector2(-169.0f, -47.0f));
	_isUnbeatableH = true;
}

void BossHead::UnbeatableToIdleH()
{
	if (_isUnbeatableH == true)
		_unbeatableTimeH += DELTA_TIME;

	if (_unbeatableTimeH < 0.2f)
		return;
	_curstate = IDLE;
	_col->SetPosition(Vector2(-169.0f, -67.0f));
	_isUnbeatableH = false;
	_unbeatableTimeH = 0.0f;
	SetRGB(0.0f, 0.0f, 0.0f);
}
