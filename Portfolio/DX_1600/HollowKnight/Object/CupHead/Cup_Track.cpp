#include "framework.h"
#include "Cup_Track.h"

Cup_Track::Cup_Track(Vector2 pos)
{
	_quad = make_shared<Quad>(L"Resource/CupHead/Track.png", Vector2(250, 50));
	_col = make_shared<RectCollider>(Vector2(250, 50));
	_transform = make_shared<Transform>();

	_trackHalfSize = _quad->GetQuadHalfSize();

	_transform->SetParent(_col->GetTransform());
	_col->GetTransform()->SetPosition(pos);
}

Cup_Track::~Cup_Track()
{
}

void Cup_Track::Update()
{
	if (_isActive == false)
		return;
	_col->Update();
	_transform->Update();
}

void Cup_Track::Render()
{
	if (_isActive == false)
		return;
	_transform->SetBuffer(0);
	_quad->Render();
	_col->Render();
}
