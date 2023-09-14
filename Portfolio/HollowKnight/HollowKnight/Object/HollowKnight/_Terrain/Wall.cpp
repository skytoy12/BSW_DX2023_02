#include "framework.h"
#include "Wall.h"


Wall::Wall(Vector2 colSize)
	:_width(colSize.x), _height(colSize.y)
{
	_transform = make_shared<Transform>();
	_col = make_shared<RectCollider>(colSize);
	_jumpCol = make_shared<RectCollider>(Vector2(colSize.x , 1.0f));


	_jumpCol->SetParent(_col->GetTransform());
	_jumpCol->SetBlue();
	_jumpCol->SetPosition(Vector2(0.0f, colSize.y * 0.5f));
}

Wall::~Wall()
{
}

void Wall::Update()
{
	_col->Update();
	_jumpCol->Update();

	BlockTarget();
}

void Wall::Render()
{
	_col->Render();
	_jumpCol->Render();
}

void Wall::BlockTarget()
{
	if (_target.expired() == true)
		return;

#define TWorldP _target.lock()->GetCollider()->GetTransform()->GetWorldPosition()
#define JCWorldP _jumpCol->GetTransform()->GetWorldPosition()
#define CWorldP _col->GetTransform()->GetWorldPosition()

	if (_jumpCol->IsCollision(_target.lock()->GetCollider()) && TWorldP.y > JCWorldP.y && TWorldP.x > CWorldP.x - (_width * 0.5f) && TWorldP.x < CWorldP.x + (_width * 0.5f))
	{
		if (_target.lock()->GetIsJump() == false)
		{
			_target.lock()->SetJumpPower(-600.0f);
		}

		_target.lock()->SetIsJump(false);
	}


	_col->Block(_target.lock()->GetCollider());
}

void Wall::BlockR(shared_ptr<RectCollider> col)
{
	_col->Block(col);
}

void Wall::BlockC(shared_ptr<CircleCollider> col)
{
	_col->Block(col);
}

void Wall::SetScale(Vector2 scale)
{
	_col->SetScale(scale);

	_width  *= scale.x;
	_height *= scale.y;

	_jumpCol->SetScale(Vector2(0.98f, 1 / scale.y));
}
