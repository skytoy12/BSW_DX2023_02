#include "Framework.h"
#include "TessellationScene.h"
TessellationScene::TessellationScene()
{
	material = new Material(L"23Triangle");

	  hullShader = Shader::GetHS(L"23Triangle");
	domainShader = Shader::GetDS(L"23Triangle");

	vertices =
	{
		{ -0.9f, -0.9f,  0.0f },
		{  0.0f, +0.9f,  0.0f },
		{ +0.9f, -0.9f,  0.0f },
	};

	vertexBuffer = new VertexBuffer(vertices);

	  edgeBuffer = new FloatValueBuffer();
	insideBuffer = new FloatValueBuffer();

	  edgeBuffer->data = {1, 1, 1, 1};
	insideBuffer->data = {1, 1, 1, 1};
}

TessellationScene::~TessellationScene()
{
	delete material;
	delete vertexBuffer;
	delete edgeBuffer;
	delete insideBuffer;
}

void TessellationScene::Update()
{
}

void TessellationScene::PreRender()
{
}

void TessellationScene::Render()
{
	  edgeBuffer->SetHSBuffer(10);
	insideBuffer->SetHSBuffer(11);

	material->SetMaterial();

	hullShader->SetShader();
	domainShader->SetShader();

	vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	DC->Draw(vertices.size(), 0);

}

void TessellationScene::PostRender()
{
	ImGui::Text("TessFactor Option");
	ImGui::DragFloat("Edge0", &edgeBuffer->data.values[0]);
	ImGui::DragFloat("Edge1", &edgeBuffer->data.values[1]);
	ImGui::DragFloat("Edge2", &edgeBuffer->data.values[2]);
	ImGui::DragFloat("inside", &edgeBuffer->data.values[3]);
}
