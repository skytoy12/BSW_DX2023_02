#include "framework.h"
#include "DungreedBullet.h"

DungreedBullet::DungreedBullet(wstring file, Vector2 scale)
	: _scale(scale), _isActive(false)
{
	_quad = make_shared<Quad>(file);
	_quad->GetTransform()->SetScale(scale);

}

DungreedBullet::~DungreedBullet()
{
}

void DungreedBullet::Update()
{
	if (_isActive == true)
	{
		_quad->GetTransform()->AddVector2(Vector2(1, 0));
	}
	_quad->Update();
}

void DungreedBullet::Render()
{
	if (_isActive == true)
	{
		_quad->Render();
	}
}
