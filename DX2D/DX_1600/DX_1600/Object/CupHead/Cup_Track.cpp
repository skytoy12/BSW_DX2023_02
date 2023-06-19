#include "framework.h"
#include "Cup_Track.h"

Cup_Track::Cup_Track()
{
	_quad = make_shared<Quad>(L"Resource/CupHead/Track.png");
	_transform = make_shared<Transform>();
	Vector2 trackSize = _quad->GetQuadHalfSize();
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 75));

	_col->GetTransform()->SetPosition(Vector2(0.0f, CENTER.y * -1.0f));
}

Cup_Track::~Cup_Track()
{
}

void Cup_Track::Update()
{
	_transform->Update();
	_col->Update();
}

void Cup_Track::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_col->Render();
}
