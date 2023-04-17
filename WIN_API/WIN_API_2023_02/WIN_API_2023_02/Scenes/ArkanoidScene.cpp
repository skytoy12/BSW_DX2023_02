#include "framework.h"
#include "ArkanoidScene.h"

ArkanoidScene::ArkanoidScene()
{
	_arkanoid = make_shared<ArkanoidBlocks>();
	_arkanoidFrame = make_shared<Frame>();
	_bar = make_shared<Bar>();
}

ArkanoidScene::~ArkanoidScene()
{
	
}

void ArkanoidScene::Update()
{
	_arkanoid->Update();
	_arkanoidFrame->Update();
	_bar->Update();
	
	
	for (auto blocksY : _arkanoid->GetBlocks())
	{
		for (auto arkanoidBlock : blocksY)
		{
			

			if (arkanoidBlock->GetEachBlock()->IsCollision(_bar->GetBallByBar()->GetBall()) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().y - 5 > (arkanoidBlock->GetEachBlock()->GetCenter().y) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().x + 5 > (arkanoidBlock->GetEachBlock()->GetCenter().x - 25) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().x - 5 < (arkanoidBlock->GetEachBlock()->GetCenter().x + 25) &&
				_bar->GetBallByBar()->GetDir().y < 0)

			{
				if (arkanoidBlock->IsAlive() == false)
					return;
				_bar->GetBallByBar()->SetDir(Vector2(_bar->GetBallByBar()->GetDir().x, (_bar->GetBallByBar()->GetDir().y * -1)));
				if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::HARDBLOCK)
					arkanoidBlock->SetType(ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK);
				else if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK)
					arkanoidBlock->SetAlive(false);
				return;
			}

			if (arkanoidBlock->GetEachBlock()->IsCollision(_bar->GetBallByBar()->GetBall()) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().y + 5 < (arkanoidBlock->GetEachBlock()->GetCenter().y) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().x + 5 > (arkanoidBlock->GetEachBlock()->GetCenter().x - 25) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().x - 5 < (arkanoidBlock->GetEachBlock()->GetCenter().x + 25) &&
				_bar->GetBallByBar()->GetDir().y > 0)
			{
				if (arkanoidBlock->IsAlive() == false)
					return;
				_bar->GetBallByBar()->SetDir(Vector2(_bar->GetBallByBar()->GetDir().x, (_bar->GetBallByBar()->GetDir().y * -1)));
				if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::HARDBLOCK)
					arkanoidBlock->SetType(ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK);
				else if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK)
					arkanoidBlock->SetAlive(false);
				return;
			}

			if (arkanoidBlock->GetEachBlock()->IsCollision(_bar->GetBallByBar()->GetBall()) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().x + 5 < (arkanoidBlock->GetEachBlock()->GetCenter().x) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().y + 5 >(arkanoidBlock->GetEachBlock()->GetCenter().y - 10) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().y - 5 < (arkanoidBlock->GetEachBlock()->GetCenter().y + 10) &&
				_bar->GetBallByBar()->GetDir().x > 0)
			{
				if (arkanoidBlock->IsAlive() == false)
					return;
				_bar->GetBallByBar()->SetDir(Vector2((_bar->GetBallByBar()->GetDir().x * -1), _bar->GetBallByBar()->GetDir().y));
				if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::HARDBLOCK)
					arkanoidBlock->SetType(ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK);
				else if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK)
					arkanoidBlock->SetAlive(false);
				return;
			}
			
			if (arkanoidBlock->GetEachBlock()->IsCollision(_bar->GetBallByBar()->GetBall()) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().x - 5 > (arkanoidBlock->GetEachBlock()->GetCenter().x) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().y + 5 > (arkanoidBlock->GetEachBlock()->GetCenter().y - 10) &&
				_bar->GetBallByBar()->GetBall()->GetCenter().y - 5 < (arkanoidBlock->GetEachBlock()->GetCenter().y + 10) &&
				_bar->GetBallByBar()->GetDir().x < 0)
			{
				if (arkanoidBlock->IsAlive() == false)
					return;
				_bar->GetBallByBar()->SetDir(Vector2((_bar->GetBallByBar()->GetDir().x * -1), _bar->GetBallByBar()->GetDir().y));
				if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::HARDBLOCK)
					arkanoidBlock->SetType(ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK);
				else if (arkanoidBlock->GetType() == ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK)
					arkanoidBlock->SetAlive(false);
				return;
			}
		}
	}
}

void ArkanoidScene::Render(HDC hdc)
{
	_arkanoidFrame->Render(hdc);
	_arkanoid->Render(hdc);
	_bar->Render(hdc);
}
