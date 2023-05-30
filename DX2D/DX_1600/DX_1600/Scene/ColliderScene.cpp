#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(50.0f, 50.0f));
	_rectCollider2 = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_circleCollider = make_shared<CircleCollider>(50.0f);
	_circleCollider2 = make_shared<CircleCollider>(100.0f);


	_rectCollider->SetPosition(CENTER);
	_rectCollider->SetScale(Vector2(2.0f, 2.0f));
	_rectCollider2->SetPosition(CENTER);

}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->Update();
	_rectCollider2->Update();
	_circleCollider->Update();
	_circleCollider2->Update();

	if (_circleCollider2->IsCollision(_rectCollider2))
	{
		_circleCollider2->SetRed();
	}
	else
		_circleCollider2->SetGreen();



	_circleCollider->SetPosition(MOUSE_POS);
	// _circleCollider->Block(_circleCollider2);

	_circleCollider2->GetTransform()->SetPosition(MOUSE_POS);
	_circleCollider2->Block(_rectCollider2);
}

void ColliderScene::Render()
{
	_rectCollider->Render();
	_rectCollider2->Render();
	_circleCollider->Render();
	_circleCollider2->Render();
}

void ColliderScene::PostRender()
{
	//ImGui::SliderFloat2("CirclePos", (float*)&_circlePos, 0, 1280);
	//_circleCollider->SetPosition(_circlePos);
}
