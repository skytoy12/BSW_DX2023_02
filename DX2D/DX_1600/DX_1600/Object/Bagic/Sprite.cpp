#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, Vector2 size)
	: _maxFrame(nullptr)
	, Quad(path, size)
{
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionFilterPS.hlsl");

	_actionFilterBuffer = make_shared<ActionFilterBuffer>();
	_actionFilterBuffer->_data.imageSize = _srv.lock()->GetImageSize();
	_actionFilterBuffer->_data.radialCenter = Vector2(0.5f, 0.5f);
}

Sprite::Sprite(wstring path, Vector2 maxFrame, Vector2 size)
	: _maxFrame(nullptr)
	, Quad(path, size)
{
	// 칸대로 잘 나뉘어져 있는 스프라이트가 생성될 경우
	_maxFrame = make_shared<Vector2>(maxFrame);
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionFilterPS.hlsl");

	_actionFilterBuffer = make_shared<ActionFilterBuffer>();
	_actionFilterBuffer->_data.imageSize = _srv.lock()->GetImageSize();
	_actionFilterBuffer->_data.radialCenter = Vector2(0.5f, 0.5f);
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	_actionFilterBuffer->Update();
}

void Sprite::Render()
{
	_actionFilterBuffer->SetPSBuffer(0);
	Quad::Render();
}

void Sprite::SetCurFrame(Vector2 frame)
{
	if (_maxFrame == nullptr)
		return;

	Vector2 size;
	size.x = _actionFilterBuffer->_data.imageSize.x / (*_maxFrame).x;
	size.y = _actionFilterBuffer->_data.imageSize.y / (*_maxFrame).y;
	
	_actionFilterBuffer->_data.startPos.x = frame.x * size.x;
	_actionFilterBuffer->_data.startPos.y = frame.y * size.y;
	_actionFilterBuffer->_data.size = size;
}

void Sprite::SetCurFrame(Action::Clip clip)
{
	_actionFilterBuffer->_data.startPos = clip._startPos;
	_actionFilterBuffer->_data.size = clip._size;
}
