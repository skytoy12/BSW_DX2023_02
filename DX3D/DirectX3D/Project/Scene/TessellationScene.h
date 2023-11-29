#pragma once
class TessellationScene : public Scene
{
public:
	TessellationScene();
	~TessellationScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	Material* material;

	HullShader* hullShader;
	DomainShader* domainShader;

	VertexBuffer* vertexBuffer;

	vector<Vertex> vertices;

	FloatValueBuffer* edgeBuffer;
	FloatValueBuffer* insideBuffer;
};



