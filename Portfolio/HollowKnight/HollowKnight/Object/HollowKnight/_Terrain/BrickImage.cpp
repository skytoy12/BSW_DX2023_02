#include "framework.h"
#include "BrickImage.h"

BrickImage::BrickImage(wstring path, Vector2 size)
{
}

BrickImage::~BrickImage()
{
}

void BrickImage::Update()
{
}

void BrickImage::Render()
{
}

void BrickImage::Save(string name, wstring flie)
{
	vector<BlockInfo> blockInfo;

	for (auto track : _tracks)
	{
		if (track->_isActive == true)
		{
			BlockInfo info;
			Vector2 pos = track->GetPosition();
			info.pos = pos;

			blockInfo.push_back(info);
		}
	}

	BinaryWriter writer = BinaryWriter(flie);
	writer.String(name);
	writer.UInt(blockInfo.size());
	writer.Byte(blockInfo.data(), sizeof(BlockInfo) * blockInfo.size());
}

void BrickImage::Load(string name, wstring flie)
{
	vector<BlockInfo> blockInfo;

	BinaryReader reader = BinaryReader(flie);
	string infoName = reader.String();

	if (infoName == "BlockInfo")
	{
		UINT size = reader.UInt();
		blockInfo.resize(size);

		void* ptr = blockInfo.data();
		reader.Byte(&ptr, size * sizeof(BlockInfo));
	}

	for (int i = 0; i < blockInfo.size(); i++)
	{
		if (i >= _tracks.size() - 1)
			break;

		_tracks[i]->SetPosition(blockInfo[i].pos);
		_tracks[i]->_isActive = true;
	}
}
