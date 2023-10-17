#include "Framework.h"
#include "ModelAnimation.h"

ModelAnimation::ModelAnimation(string name, wstring shaderFile)
	:name(name)
{
	reader = new ModelReader(name);
	reader->SetShader(shaderFile);

	frameBuffer = new FrameBuffer();
}

ModelAnimation::~ModelAnimation()
{
	delete reader;

	delete frameBuffer;
}

void ModelAnimation::Update()
{
	Transform::Update();

	static float time = 0.0f;
	time += Time::Delta();

	frameBuffer->data.curFrame = time;
}

void ModelAnimation::Render()
{
	Transform::SetWorld();

	frameBuffer->SetVSBuffer(3);
	DC->VSSetShaderResources(0, 1, &srv);

	reader->Render();
}

void ModelAnimation::ReadClip(string file, UINT clipIndex)
{
	string path = "_ModelData / Clip / " + name + " / " + file + to_string(clipIndex) + ".clip";

	BinaryReader data(path);

	ModelClip* clip = new ModelClip();

	clip->name           = data.ReadString();
	clip->ticksPerSecond = data.ReadFloat();
	clip->frameCount     = data.ReadUINT();
	clip->duration       = data.ReadFloat();
	
	UINT keyFrameCount = data.ReadUINT();

	for (UINT i = 0; i < keyFrameCount; i++)
	{
		KeyFrame* keyFrame = new KeyFrame;
		keyFrame->boneName = data.ReadString();

		UINT keyTransformCount = data.ReadUINT();

		if (keyTransformCount > 0)
		{
			keyFrame->transforms.resize(keyTransformCount);

			void* ptr = (void*)keyFrame->transforms.data();
			data.ReadData(&ptr, sizeof(KeyTransform) * keyTransformCount);
		}

		clip->keyFrames.emplace(keyFrame->boneName, keyFrame);
	}

	clips.emplace_back(clip);
}

void ModelAnimation::CreateTexture()
{
	UINT clipCount = clips.size();

	clipTransform = new ClipTransform[clipCount];
	nodeTransform = new ClipTransform[clipCount];

	for (UINT i = 0; i < clipCount; i++)
	{
		CreateClipTransform(i);
	}

	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width            = MAX_BONE * 4;
	desc.Height           = MAX_FRAME_KEY;
	desc.ArraySize        = clipCount;
	desc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage            = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels        = 1;
	desc.SampleDesc.Count = 1;

	UINT pageSize = MAX_BONE * sizeof(Matrix) * MAX_FRAME_KEY;

	void* ptr = VirtualAlloc(nullptr, pageSize * clipCount, MEM_RESERVE, PAGE_READWRITE);

	for (UINT c = 0; c < clipCount; c++)
	{
		UINT start = c * pageSize;

		for (UINT i = 0; i < MAX_FRAME_KEY; i++)
		{
			void* temp = (BYTE*)ptr + MAX_BONE * i * sizeof(Matrix) + start;

			VirtualAlloc(temp, MAX_BONE * sizeof(Matrix), MEM_COMMIT, PAGE_READWRITE);
			memcpy(temp, clipTransform[c].transform[i], MAX_BONE * sizeof(Matrix));
		}
	}

	D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[clipCount];

	for (UINT c = 0; c < clipCount; c++)
	{
		void* temp = (BYTE*)ptr + c * pageSize;

		subResource[c].pSysMem = temp;
		subResource[c].SysMemPitch = MAX_BONE * sizeof(Matrix);
		subResource[c].SysMemSlicePitch = pageSize;
	}

	DEVICE->CreateTexture2D(&desc, subResource, &texture);

	delete[] subResource;
	VirtualFree(ptr, 0, MEM_RELEASE);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format                   = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension            = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.ArraySize = clipCount;

	DEVICE->CreateShaderResourceView(texture, &srvDesc, &srv);
}

void ModelAnimation::CreateClipTransform(UINT index)
{
	ModelClip* clip = clips[index];

	for (UINT f = 0; f < clip->frameCount; f++)
	{
		UINT nodeIndex = 0;

		for (NodeData node : reader->nodes)
		{
			Matrix animWorld;
			KeyFrame* frame = clip->GetKeyFrames(node.name);

			if (frame != nullptr)
			{
				KeyTransform transform = frame->transforms[f];

				Matrix S = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
				Matrix R = XMMatrixRotationQuaternion(XMLoadFloat4(&transform.rotation));
				Matrix T = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);

				animWorld = S * R * T;
			}
			else
			{
				animWorld = XMMatrixIdentity();
			}

			Matrix parentWorld;

			int parentIndex = node.parent;

			if (parentIndex < 0)
				parentWorld = XMMatrixIdentity();
			else
				parentWorld = nodeTransform[index].transform[f][parentIndex];

			nodeTransform[index].transform[f][nodeIndex] = animWorld * parentWorld;

			vector<BoneData> bones = reader->bones;

			if (reader->HasBone(node.name))
			{
				UINT boneIndex = reader->boneMap[node.name];

				Matrix transform = bones[boneIndex].offset;

				transform *= nodeTransform[index].transform[f][nodeIndex];

				clipTransform[index].transform[f][boneIndex] = transform;
			}

			nodeIndex++;
		}
	}
}
