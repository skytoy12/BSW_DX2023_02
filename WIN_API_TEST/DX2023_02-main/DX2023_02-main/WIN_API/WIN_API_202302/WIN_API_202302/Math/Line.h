#pragma once
class Line
{
public:
	Line(Vector2 start, Vector2 end);
	~Line();

	void Update();
	void Render(HDC hdc);

	Vector2 GetVector2() { return (_end - _start); }

	ColResult_Line IsCollision(shared_ptr<Line> other);
	float Slope() { return (_end.y - _start.y) / (_end.x - _start.x); }
	float Y_intercept() { return _start.y - (this->Slope() * _start.x); }

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

public:
	vector<HPEN> _pens;
	UINT _curPen = 0;

	Vector2 _start;
	Vector2 _end;
};

