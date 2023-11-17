#pragma once
class Rain : public Particle
{
public:
	Rain(wstring file);
	~Rain();

	void Update() override;
	void Render() override;
	void  Debug() override;

private:
	virtual void SetVertex() override;

private:
	vector<VertexTexture> vertices;

	WeatherBuffer* buffer;
};


