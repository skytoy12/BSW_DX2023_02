#include "framework.h"
#include "VectorBrick.h"

VectorBrick::VectorBrick()
{

}

VectorBrick::~VectorBrick()
{
}

void VectorBrick::Update()
{
}

void VectorBrick::Render()
{
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