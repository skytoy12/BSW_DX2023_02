#include "framework.h"
#include "VectorBrick.h"

VectorBrick::VectorBrick()
{
	for (int i = 0; i < 10; i++)
	{
		shared_ptr<BrickImage> brick = make_shared<BrickImage>(L"Resource/UI/Title.png", Vector2(1185.0f * 0.5f, 412.0f * 0.5f));
	}
}

VectorBrick::~VectorBrick()
{
}

void VectorBrick::Update()
{
	for (shared_ptr<BrickImage> brick : _brickImages)
	{
		brick->Update();
	}
}

void VectorBrick::Render()
{
	for (shared_ptr<BrickImage> brick : _brickImages)
	{
		brick->Render();
	}
}

void VectorBrick::Save(string name, wstring flie)
{
	vector<BrickInfo> brickInfo;

	for (auto brick : _brickImages)
	{
		if (brick->_isActive == true)
		{
			BrickInfo info;
			Vector2 pos = brick->GetPosition();
			info.pos = pos;

			brickInfo.push_back(info);
		}
	}

	BinaryWriter writer = BinaryWriter(flie);
	writer.String(name);
	writer.UInt(brickInfo.size());
	writer.Byte(brickInfo.data(), sizeof(BrickInfo) * brickInfo.size());
}

void VectorBrick::Load(string name, wstring flie)
{
	vector<BrickInfo> brickInfo;

	BinaryReader reader = BinaryReader(flie);
	string infoName = reader.String();

	if (infoName == name)
	{
		UINT size = reader.UInt();
		brickInfo.resize(size);

		void* ptr = brickInfo.data();
		reader.Byte(&ptr, size * sizeof(BrickInfo));
	}

	for (int i = 0; i < brickInfo.size(); i++)
	{
		if (i >= _brickImages.size() - 1)
			break;

		_brickImages[i]->SetPosition(brickInfo[i].pos);
		_brickImages[i]->_isActive = true;
	}
}