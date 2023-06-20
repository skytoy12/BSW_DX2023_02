#include "framework.h"
#include "Cup_Track2.h"

Cup_Track2::Cup_Track2()
{
	_quad = make_shared<Quad>(L"Resource/CupHead/Track.png");
	_transform = make_shared<Transform>();
	_trackHalfSize = _quad->GetQuadHalfSize();
	_col = make_shared<RectCollider>(_trackHalfSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 75));

	_col->GetTransform()->SetPosition(Vector2(1700.0f, CENTER.y * -1.0f + 200.0f));
}

Cup_Track2::~Cup_Track2()
{
}

void Cup_Track2::Update()
{
	_transform->Update();
	_col->Update();
}

void Cup_Track2::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_col->Render();
}
