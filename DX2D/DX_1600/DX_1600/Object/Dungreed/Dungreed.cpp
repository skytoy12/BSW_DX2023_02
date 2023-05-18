#include "framework.h"
#include "Dungreed.h"

Dungreed::Dungreed(wstring file, Vector2 scale)
	: _scale(scale)
{
	_quad = make_shared<Quad>(file);
	_quad->GetTransform()->SetScale(scale);

	_bow = make_shared<Transform>();
}

Dungreed::~Dungreed()
{
}

void Dungreed::Update()
{
	_bow->SetPosition(Vector2(0, 0));
	_quad->Update();
	_bow->Update();
}

void Dungreed::Render()
{
	_quad->Render();
}
