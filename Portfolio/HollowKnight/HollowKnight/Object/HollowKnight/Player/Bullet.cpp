#include "framework.h"
#include "Bullet.h"

using namespace tinyxml2;

Bullet::Bullet()
{
	_transform = make_shared<Transform>();
	_col = make_shared<CircleCollider>(5);

	CreateAction(L"Resource/Bullet/Bullet.png", "Resource/Bullet/Bullet.xml", "Bullet", Vector2(266, 116), Action::Type::END);
	CreateAction(L"Resource/Bullet/BulletEnd.png", "Resource/Bullet/BulletEnd.xml", "BulletEnd", Vector2(207, 85), Action::Type::END);

	_transform->SetParent(_col->GetTransform());
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_isActive == false)
		return;

	if (_dir.x > 0)
		SetRight();
	if (_dir.x < 0)
		SetLeft();
	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	_col->Update();
	_transform->Update();
	_actions[_state]->Update();
	_sprites[_state]->Update();

	_length += DELTA_TIME;
	if (_length > 1.0f)
		_isActive = false;

	if (!_isActive)
	{
		_state = IDLE;
		_actions[_state]->Reset();
		_length = 0.0f;
	}
}

void Bullet::Render()
{
	if (_isActive == false)
		return;
	_transform->SetBuffer(0);

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();

	_col->Render();
}

void Bullet::Shoot(Vector2 startPos, Vector2 dir)
{
	_actions[_state]->Update();
	_isActive = true;

	_actions[IDLE]->Play();
	_actions[END]->Reset();

	_col->GetTransform()->SetPosition(startPos);
	_dir = dir.NormalVector2();
}

void Bullet::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

void Bullet::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
	_isLeft = true;
}

void Bullet::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
	_isLeft = false;
}
