#include "Framework.h"
#include "TerrainEditor.h"

TerrainEditor::TerrainEditor(UINT height, UINT width)
	:height(height), width(width)
{
	material = new Material();
	material->SetShader(L"TerrainBrush");

	worldBuffer = new MatrixBuffer();

	CreateMesh();
	CreateNormal();
	CreateTangent();

	mesh = new Mesh(vertices, indices);

	rayBuffer = new RayBuffer();
	computeShader = Shader::GetCS(L"ComputePicking");

	polygonCount = indices.size() / 3;

	input = new InputDesc[polygonCount];

	for (UINT i = 0; i < polygonCount; i++)
	{
		input[i].index = i;

		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		input[i].v0 = vertices[index0].pos;
		input[i].v1 = vertices[index1].pos;
		input[i].v2 = vertices[index2].pos;
	}

	structuredBuffer = new StructuredBuffer
	                  (   input, 
						  sizeof(InputDesc),
						  polygonCount, 
						  sizeof(OutputDesc), 
						  polygonCount
					  );

	output = new OutputDesc[polygonCount];

	brushBuffer = new BrushBuffer();
}

TerrainEditor::~TerrainEditor()
{
	delete mesh;
	delete worldBuffer;
	delete material;

	delete[] input;
	delete[] output;

	delete        rayBuffer;
	delete structuredBuffer;
	delete brushBuffer;

}

void TerrainEditor::Update()
{
	Transform::Update();
	Picking(&pickedPos);

	brushBuffer->data.location = pickedPos;

	if (KEY_PRESS(VK_LBUTTON))
		AdjustHeight();
}

void TerrainEditor::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);

	brushBuffer->SetPSBuffer(10);


	mesh->SetMesh();
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TerrainEditor::Debug()
{
	ImGui::Text("PickedPos : %.1f, %.1f,%.1f", pickedPos.x, pickedPos.y, pickedPos.z);
	ImGui::ColorEdit3("BrushColor", (float*)&brushBuffer->data.color);
}

bool TerrainEditor::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(mousePos);

	rayBuffer->data.origin     = ray.origin;
	rayBuffer->data.direction  = ray.direction;
	rayBuffer->data.outputSize = polygonCount;

	rayBuffer->SetCSBuffer(0);

	//////////////////////////////

	structuredBuffer->SetSRV();
	structuredBuffer->SetUAV();

	computeShader->SetShader();

	UINT groupCount = ceil(polygonCount / 1024.0f);

	DC->Dispatch(groupCount, 1, 1);

	structuredBuffer->Copy(output, sizeof(OutputDesc) * polygonCount);

	for (UINT i = 0; i < polygonCount; i++)
	{
		if (output[i].isPicked)
		{
			*position = ray.origin + ray.direction * output[i].distance;

			return true;
		}
	}

	return false;
}

void TerrainEditor::CreateMesh()
{

	//Vertices
	for (float z = 0; z < height; z++)
	{
		for (float x = 0; x < width; x++)
		{
			VertexType vertex;
			vertex.pos = Vector3(x, 0, z);

			vertex.uv.x = x / (width - 1);
			vertex.uv.y = 1 - z / (height - 1);


			vertices.push_back(vertex);
		}
	}

	//Indices
	for (float z = 0; z < height - 1; z++)
	{
		for (float x = 0; x < width - 1; x++)
		{
			indices.push_back((x + 0) + width * (z + 1));  //7
			indices.push_back((x + 1) + width * (z + 1));  //8
			indices.push_back((x + 0) + width * (z + 0));  //0

			indices.push_back((x + 0) + width * (z + 0));  //0
			indices.push_back((x + 1) + width * (z + 1));  //8
			indices.push_back((x + 1) + width * (z + 0));  //1
		}
	}
}

void TerrainEditor::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		Vector3 v01 = p1 - p0;
		Vector3 v02 = p2 - p0;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}
}

void TerrainEditor::CreateTangent()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		Vector2 uv0 = vertices[index0].uv;
		Vector2 uv1 = vertices[index1].uv;
		Vector2 uv2 = vertices[index2].uv;

		Vector3 e01 = p1 - p0;
		Vector3 e02 = p2 - p0;

		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;

		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		float D = 1.0f / (u1 * v2 - v1 * u2);

		Vector3 tangent = D * (e01 * v2 - e02 * v1);

		vertices[index0].tangent += tangent;
		vertices[index1].tangent += tangent;
		vertices[index2].tangent += tangent;
	}

	for (VertexTextureNormalTangent& vertex : vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = (T - N * Vector3::Dot(N, T)).GetNormalized();
	}
}

void TerrainEditor::AdjustHeight()
{
	switch (brushBuffer->data.type)
	{
	case 0:
		for (VertexType& vertex : vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3( pickedPos.x, 0.0f,  pickedPos.z);

			float distance = (p1 - p2).Length();

			if (distance <= brushBuffer->data.range)
			{
				vertex.pos.y += 10 * Time::Delta();
			}
		}
		break;
	default:
		break;
	}

	mesh->UpdateVertex(vertices.data(), vertices.size());
}
