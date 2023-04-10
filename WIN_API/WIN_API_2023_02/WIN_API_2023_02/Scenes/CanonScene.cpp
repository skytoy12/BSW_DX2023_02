#include "framework.h"
#include "CanonScene.h"

CanonScene::CanonScene()
{
	_canon = make_shared<Canon>(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
	
	_canonEnemy = make_shared<Canon>(Vector2(WIN_WIDTH * 0.5f + 300.0, WIN_HEIGHT * 0.5f));

	_canon->SetTurn(true);
	_canonEnemy->SetTurn(false);

	//_canon->SetTarget(_canonEnemy);
}

CanonScene::~CanonScene()
{
}

void CanonScene::Update()
{
	_canon->Update();
	_canonEnemy->Update();

	// ĳ���� ����ִ� �Ѿ� 30���� ���ʹ��� �浹�˻�
	for (auto bullet : _canon->GetBullets())
	{
		if (bullet->IsCollision(_canonEnemy))
		{
			bullet->SetActive(false);
		}
	}
}

void CanonScene::Render(HDC hdc)
{
	_canon->Render(hdc);
	_canonEnemy->Render(hdc);
}
