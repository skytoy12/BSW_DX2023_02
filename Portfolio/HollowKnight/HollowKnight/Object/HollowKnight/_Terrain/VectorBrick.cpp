#include "framework.h"
#include "VectorBrick.h"

VectorBrick::VectorBrick()
{
	for (int i = 0; i < 50; i++)
	{
		shared_ptr<BrickImage> brick = make_shared<BrickImage>(L"Resource/Ceil/11.png", Vector2(275.0f, 273.0f));
		brick->_isActive = false;
		_brickImages.push_back(brick);
	}
}

VectorBrick::~VectorBrick()
{
}

void VectorBrick::Update()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_DOWN('S'))
			Save(_name, _savefile);
	}

	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_DOWN('V'))
			Load(_name, _savefile);
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		for (auto brick : _brickImages)
		{
			if (brick->_isActive == false)
			{
				brick->SetPosition(W_MOUSE_POS);
				brick->_isActive = true;
				break;
			}
		}
	}
	
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
			Vector2 scale = brick->GetScale();
			wstring path = brick->Getpath();

			info.pos = pos;
			info.Scale = scale;
			info.path = path;

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
		//wstring temp = brickInfo[i].path;
		_brickImages[i]->SetPosition(brickInfo[i].pos);
		_brickImages[i]->SetScale(brickInfo[i].Scale);
		_brickImages[i]->SetSRV(brickInfo[i].path);
		_brickImages[i]->_isActive = true;
	}
}