#pragma once
class Black
{
public:
	Black();
	~Black();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

	void SetAlphaBuffer(float value) { _alphaBuffer->_data.alpha = value; }

	void FadeOut();

	float GetAlpha() { return _alphaBuffer->_data.alpha; }
private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<AlphaBuffer> _alphaBuffer;
};


