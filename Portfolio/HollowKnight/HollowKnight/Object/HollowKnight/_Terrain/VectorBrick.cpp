#include "framework.h"
#include "VectorBrick.h"

VectorBrick::VectorBrick()
{
	for (int i = 0; i < 100; i++)
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
			SavePS(_name, _savefile);
			SaveWString(_image);
		}

	}

	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_DOWN('V'))
		{
			LoadPS(_name, _savefile);
			LoadWString(_image);
		}
		
	}

	if (KEY_PRESS(VK_CONTROL))
	{
		if (KEY_DOWN('Z'))
		{
			_brickImages[_curNum]->ReturnPos();
		}

	}

	if (KEY_DOWN(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
	{
		if (KEY_PRESS(VK_LSHIFT))
		{
			if (_brickImages[_curNum]->_isActive == false)
				_brickImages[_curNum]->_isActive = true;

			_brickImages[_curNum]->SetPosition(W_MOUSE_POS);
		}
	}

	if (KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
	{
		if (KEY_PRESS(VK_CONTROL))
		{
			if (_brickImages[_curNum]->_isActive == false)
				_brickImages[_curNum]->_isActive = true;

			_brickImages[_curNum]->SetPosition(W_MOUSE_POS);
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

void VectorBrick::PostRender()
{
	ImGui::SliderFloat("BrickScale.x", &_brickScaleX, 0.0f, 5.0f);
	ImGui::SliderFloat("BrickScale.y", &_brickScaleY, 0.0f, 5.0f);

	ImGui::SliderFloat("BrickPos.x", &_brickPosX, -10000.0f, 10000.0f);
	ImGui::SliderFloat("BrickPos.y", &_brickPosY, -10000.0f, 10000.0f);

	ImGui::SliderInt("CurNumber", &_curNum, 0, 49);
	ImGui::SliderInt("imageNumber", &_imagenumber, 0, 200);

	ImGui::Text("Pos = %.1f, %.1f", _brickImages[_curNum]->GetPosition().x, _brickImages[_curNum]->GetPosition().y);
	ImGui::Text("Scale = %.1f, %.1f", _brickImages[_curNum]->GetScale().x, _brickImages[_curNum]->GetScale().y);

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

	if (ImGui::Button("Scale"))
	{
		_brickImages[_curNum]->SetScale(Vector2(_brickScaleX, _brickScaleY));
	}

	if (ImGui::Button("Pos"))
	{
		_brickImages[_curNum]->SetPosition(Vector2(_brickPosX, _brickPosY));
	}
}

void VectorBrick::SavePS(string name, wstring file)
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

	BinaryWriter writer = BinaryWriter(file);
	writer.String(name);
	writer.UInt(brickInfo.size());
	writer.Byte(brickInfo.data(), sizeof(BrickInfo) * brickInfo.size());
}

void VectorBrick::LoadPS(string name, wstring file)
{
	vector<BrickInfo> brickInfo;

	BinaryReader reader = BinaryReader(file);
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

void VectorBrick::SaveWString(wstring file)
{
	BinaryWriter data(file);

	for (shared_ptr<BrickImage> image : _brickImages)
	{
		wstring temp = image->Getpath();
		data.WString(temp);
	}
}

void VectorBrick::LoadWString(wstring file)
{
	BinaryReader data(file);

	for (shared_ptr<BrickImage> image : _brickImages)
	{
		image->SetSRV(data.WString());
	}
	
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
