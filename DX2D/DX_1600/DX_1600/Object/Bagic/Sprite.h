#pragma once
class Sprite : public Quad
{
public :
	Sprite(wstring path, Vector2 size);
	Sprite(wstring path, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite();

	void Update();
	virtual void Render() override;

	void SetCurFrame(Vector2 frame);
	void SetCurFrame(Action::Clip clip);

	void SetLeft() { _actionFilterBuffer->_data.isRight = 0; }
	void SetRight() { _actionFilterBuffer->_data.isRight = 1; }

	void SetSelected(int value) { _actionFilterBuffer->_data.selected = value; }
	void SetValue1(int value) { _actionFilterBuffer->_data.value1 = value; }
	void SetValue2(int value) { _actionFilterBuffer->_data.value2 = value; }
	void SetValue3(int value) { _actionFilterBuffer->_data.value3 = value; }
	void AddValue1(int value) { _actionFilterBuffer->_data.value1 += value; }
	void AddValue2(int value) { _actionFilterBuffer->_data.value2 += value; }
	void AddValue3(int value) { _actionFilterBuffer->_data.value3 += value; }

private :
	shared_ptr<ActionFilterBuffer> _actionFilterBuffer;

	shared_ptr<Vector2> _maxFrame;
};

