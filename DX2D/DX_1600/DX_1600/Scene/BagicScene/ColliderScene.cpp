#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(50.0f, 80.0f));
	_rectCollider2 = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_circleCollider = make_shared<CircleCollider>(50.0f);
	_circleCollider2 = make_shared<CircleCollider>(100.0f);


	_circleCollider->SetPosition(CENTER);
	_circleCollider->SetScale(2.0f);
	_rectCollider2->SetPosition(CENTER);

}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Collider_Update()
{
	_rectCollider->Update();
	_rectCollider2->Update();
	_circleCollider->Update();
	_circleCollider2->Update();


}

void ColliderScene::Update()
{

	_rectCollider2->SetPosition(MOUSE_POS);
	if (KEY_PRESS('W'))
		_rectCollider2->GetTransform()->AddAngle(5.0f * DELTA_TIME);

	if (KEY_PRESS('D'))
		_rectCollider2->GetTransform()->AddScale(Vector2(1.0f * DELTA_TIME, 0.0f));

	if (KEY_PRESS('A'))
		_rectCollider2->GetTransform()->AddScale(Vector2(-1.0f * DELTA_TIME, 0.0f));

	if (_rectCollider2->IsCollision(_circleCollider, true))
	{
		_circleCollider->SetRed();
		_rectCollider2->SetRed();
	}
	else
	{
		_circleCollider->SetGreen();
		_rectCollider2->SetGreen();
	}

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
