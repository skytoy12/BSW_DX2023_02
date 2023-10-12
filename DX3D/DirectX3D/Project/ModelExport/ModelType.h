#pragma once

typedef VertexTextureNormalTangentBlend ModelVertex;

struct MeshData
{
	string name;

	UINT materialIndex;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;
};

struct NodeData
{
	int index;

	string name;

	int parent;

	XMFLOAT4X4 transform;
};

struct BoneData
{
	int index;

	string name;

	XMFLOAT4X4 offset;
};

struct VertexWeights
{
	UINT indices[4];
	float weights[4];

	void Add(const UINT& index, const float& weight)
	{
		for (UINT i = 0; i < 4; i++)
		{
			if (weights[i] == 0.0f)
			{
				indices[i] = index;
				weights[i] = weight;
				return;
			}
		}
	}

	void Normalize()
	{
		float sum = 0.0f;

		for (UINT i = 0; i < 4; i++)
		{
			sum += weights[i];
		}

		for (UINT i = 0; i < 4; i++)
		{
			weights[i] /= sum;
		}
	}
};

struct KeyTransform
{
	float time;

	Vector3 scale;
	Vector4 rotation; // 오일러각이 아니라 쿼터니언각을 사용하므로 Vector4로 사용
	Vector3 position;
};

struct KeyFrame
{
	string boneName;

	vector<KeyTransform> transforms;
};

struct ClipNode
{
	vector<KeyTransform> KeyFrame;
	aiString name;
};

struct Clip
{
	string name;

	UINT frameCount;

	float ticksPerSecond;
	float duration;

	vector<KeyFrame*> keyFrame;
};

struct ClipTransform
{
	Matrix transform[MAX_FRAME_KEY][MAX_BONE];
};