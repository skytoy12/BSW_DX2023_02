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
		{
			SaveWString("saveee", L"Info/abc.abc");
			SavePS(_name, _savefile);
		}

	}

	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_DOWN('V'))
			LoadPS(_name, _savefile);
	}

	if (KEY_DOWN(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
	{
		if (_brickImages[_curNum]->_isActive == false)
			_brickImages[_curNum]->_isActive = true;

		_brickImages[_curNum]->SetPosition(W_MOUSE_POS);

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

void VectorBrick::PostRender()
{
	ImGui::SliderFloat("Scale.x", &_brickScaleX, 0.0f, 2.0f);
	ImGui::SliderFloat("Scale.y", &_brickScaleY, 0.0f, 2.0f);
	ImGui::SliderInt("CurNumber", &_curNum, 0, 49);
	ImGui::SliderInt("imageNumber", &_imagenumber, 0, 200);

	if (ImGui::Button("Ceil"))
	{
		_imageType = L"Ceil/";
	}

	if (ImGui::Button("Deco"))
	{
		_imageType = L"Deco/";
	}

	if (ImGui::Button("Stool"))
	{
		_imageType = L"Stool/";
	}

	if (ImGui::Button("Select"))
	{
		wstring imagenumber = to_wstring(_imagenumber);
		_select = L"Resource/" + _imageType + imagenumber + L".png";

		_brickImages[_curNum]->SetSRV(_select);
	}
}

void VectorBrick::SavePS(string name, wstring flie)
{
	vector<BrickInfo> brickInfo;

	for (auto brick : _brickImages)
	{
		if (brick->_isActive == true)
		{
			BrickInfo info;

			Vector2 pos = brick->GetPosition();
			Vector2 scale = brick->GetScale();

			info.pos = pos;
			info.Scale = scale;

			brickInfo.push_back(info);
		}
	}

	BinaryWriter writer = BinaryWriter(flie);
	writer.String(name);
	writer.UInt(brickInfo.size());
	writer.Byte(brickInfo.data(), sizeof(BrickInfo) * brickInfo.size());
}

void VectorBrick::LoadPS(string name, wstring flie)
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
		_brickImages[i]->SetScale(brickInfo[i].Scale);
		_brickImages[i]->_isActive = true;
	}
}

void VectorBrick::SaveWString(string name, wstring flie)
{
	//vector<string> files;

	//for (auto brick : _brickImages)
	//{
	//	if (brick->_isActive == true)
	//	{
	//		wstring path;
	//		string imageName;

	//		path = brick->Getpath();
	//		imageName = ToString(path);

	//		files.push_back(imageName);
	//	}
	//}

	//UINT dataSize = 0;
	//for (string file : files)
	//{
	//	dataSize += sizeof(file);
	//}

	//BinaryWriter writer = BinaryWriter(flie);
	//writer.String(name);
	//writer.UInt(dataSize);
	//for (string file : files)
	//{
	//	writer.String(file);
	//}
}

void VectorBrick::LoadWString(string name, wstring flie)
{
	//vector<string> files;

	//BinaryReader reader = BinaryReader(flie);
	//string infoName = reader.String();

	//if (infoName == name)
	//{
	//	UINT size = reader.UInt();
	//	files.resize(size);

	//	void* ptr = files.data();
	//	reader.String();
	//}

	//for (int i = 0; i < brickInfo.size(); i++)
	//{
	//	if (i >= _brickImages.size() - 1)
	//		break;

	//	_brickImages[i]->SetPosition(brickInfo[i].pos);
	//	_brickImages[i]->SetScale(brickInfo[i].Scale);
	//	_brickImages[i]->_isActive = true;
	//}
}


string VectorBrick::ToString(wstring str)
{
	string temp;

	temp.assign(str.begin(), str.end());

	return temp;
}

wstring VectorBrick::ToWString(string str)
{
	wstring temp;

	temp.assign(str.begin(), str.end());

	return temp;
}

void VectorBrick::SelectImage()
{
}
