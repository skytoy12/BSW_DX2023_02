#include "framework.h"
#include "ArkanoidBlocks.h"

ArkanoidBlocks::ArkanoidBlocks()
{
	_arkanoidBlocks.reserve(_poolCountX);
	Vector2 offset = { 400, 150 };
	for (int x = 0; x < _poolCountX; x++)
	{
		vector<shared_ptr<ArkanoidBlock>> blocksY;
		blocksY.reserve(_poolCountY);
		for (int y = 0; y < _poolCountY; y++)
		{
			int a = rand() % 2;
			shared_ptr<ArkanoidBlock> arkanoidBlocks = make_shared<ArkanoidBlock>();
			if (a == 0)
				arkanoidBlocks->SetType(ArkanoidBlock::ArkanoidBlockType::NOMALBLOCK);
			else
				arkanoidBlocks->SetType(ArkanoidBlock::ArkanoidBlockType::HARDBLOCK);
			Vector2 distance = { x * 50, y * 20 };
			arkanoidBlocks->SetPosition(offset + distance);
			blocksY.push_back(arkanoidBlocks);
		}
		_arkanoidBlocks.push_back(blocksY);
	}
}

ArkanoidBlocks::~ArkanoidBlocks()
{
}

void ArkanoidBlocks::Update()
{
	for (auto blocksY : _arkanoidBlocks)
	{
		for (auto arkanoidBlocks : blocksY)
		{
			arkanoidBlocks->Update();
		}
	}
}

void ArkanoidBlocks::Render(HDC hdc)
{
	for (auto blocksY : _arkanoidBlocks)
	{
		for (auto arkanoidBlocks : blocksY)
		{
			arkanoidBlocks->Render(hdc);
		}
	}
}
