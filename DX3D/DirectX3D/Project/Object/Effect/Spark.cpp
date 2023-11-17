#include "Framework.h"
#include "Spark.h"

Spark::Spark(wstring file, bool isAdditive)
{
	this->isAdditive = isAdditive;

	material->SetShader(L"15Spark");
	material->SetDiffuseMap(file);

	geometryShader = Shader::GetGS(L"15Spark");

	valueBuffer      = new FloatValueBuffer();
	startColorBuffer = new FloatValueBuffer();
	endColorBuffer   = new FloatValueBuffer();

	startColorBuffer->data.values[3] = 1.0f;
	endColorBuffer  ->data.values[3] = 1.0f;

	SetVertex();
}

Spark::~Spark()
{
	delete      valueBuffer;
	delete startColorBuffer;
	delete   endColorBuffer;
}

void Spark::Update()
{
	if (!isActive)
		return;

	//value0 : time
	//value1 : duration

	valueBuffer->data.values[0] += Time::Delta();

	if (valueBuffer->data.values[0] > valueBuffer->data.values[1])
		Stop();
}

void Spark::Render()
{
	      valueBuffer->SetPSBuffer(10);
	      valueBuffer->SetVSBuffer(10);
	 startColorBuffer->SetPSBuffer(11);
	   endColorBuffer->SetPSBuffer(12);

	   Particle::Render();
}

void Spark::Debug()
{
	ImGui::Text("Spark Option");

	ImGui::SliderInt("Particle Count", (int*)&drawCount, 1, MAX_COUNT);

	ImGui::ColorEdit4("StartColor", startColorBuffer->data.values);
	ImGui::ColorEdit4("EndColor"  ,   endColorBuffer->data.values);
}

void Spark::Play(Vector3 position)
{
	valueBuffer->data.values[0] = 0.0f;

	Particle::Play(position);

	UpdateParticle();
	vertexBuffer->UpdateVertex(vertices.data(), drawCount);
}

void Spark::SetVertex()
{
	vertices.resize(MAX_COUNT);

	vertexBuffer = new VertexBuffer(vertices);

	drawCount = 500;

	valueBuffer->data.values[1] = 1.0f;
}

void Spark::UpdateParticle()
{
	for (UINT i = 0; i < drawCount; i++)
	{
		vertices[i].position = position;

		float size = Random(minSize, maxSize);
		vertices[i].size = { size, size };

		Vector3 rot;

		rot.x = Random(0.0f, XM_2PI);
		rot.y = Random(0.0f, XM_2PI);
		rot.z = Random(0.0f, XM_2PI);

		float radius = Random(minRadius, maxRadius);

		Vector3 velocity = Vector3(0, 0, radius);

		Matrix rotMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);

		vertices[i].velocity = XMVector3TransformCoord(velocity, rotMatrix);
	}
}
