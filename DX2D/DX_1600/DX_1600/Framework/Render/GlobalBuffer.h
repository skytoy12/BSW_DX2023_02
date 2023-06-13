#pragma once
class MatrixBuffer : public ConstantBuffer
{
public :
	// 상수 버퍼를 이용할 때 한가지 규칙
	// 16바이트의 배수를 무조건 지켜야한다
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	MatrixBuffer()
	:ConstantBuffer(&_data, sizeof(_data))
	{

	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		value = XMMatrixTranspose(value);
		_data.matrix = value;
	}

	Data _data;

};

class ColorBuffer : public ConstantBuffer
{
public :
	struct Data
	{
		XMFLOAT4 color;
	};

	ColorBuffer()
		:ConstantBuffer(&_data, sizeof(Data))
	{
		
	}
	virtual ~ColorBuffer() {}

	void SetColor(XMFLOAT4 value) { _data.color = value; }

	Data _data;
};

class FrameBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT2 maxFrame = { 0.0f, 0.0f };
		XMFLOAT2 curFrame = { 0.0f, 0.0f };
	};

	FrameBuffer()
		:ConstantBuffer(&_data, sizeof(Data))
	{

	}
	virtual ~FrameBuffer() {}

	void SetMaxFrame(Vector2 value)
	{
		_data.maxFrame = value;
	}
	void SetCurFrame(Vector2 value)
	{
		_data.curFrame = value;
	}

	Data _data;
};

class ActionBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Vector2 startPos;
		Vector2 size;
		Vector2 imageSize;
		int isRight = 0;
		int padding;
	};

	ActionBuffer()
		:ConstantBuffer(&_data, sizeof(Data))
	{

	}
	virtual ~ActionBuffer() {}


	Data _data;
};



class FilterBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selected = 0;
		int Value1 = 0;
		int Value2 = 0;
		int Value3 = 0;

		Vector2 imageSize;
		Vector2 radialCenter;
	};

	FilterBuffer()
		:ConstantBuffer(&_data, sizeof(Data))
	{

	}
	virtual ~FilterBuffer() {}


	Data _data;
};