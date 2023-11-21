#include "Framework.h"
#include "ParticleEditorScene.h"

ParticleEditorScene::ParticleEditorScene()
{
	quad = new Quad();
	quad->GetMaterial()->SetShader(L"06TextureInstancing");
	quad->GetMaterial()->SetDiffuseMap(L"Effect/Snow.png");

	instanceData.resize(MAX_COUNT);

	instanceBuffer = new VertexBuffer(instanceData);

	Init();
}

ParticleEditorScene::~ParticleEditorScene()
{
	delete quad;
	delete instanceBuffer;
}

void ParticleEditorScene::Update()
{
	lifeTime += Time::Delta();

	UpdatePhysics();
	UpdateColor();

	quad->Update();

	if (lifeTime > data.duration)
		Init();
}

void ParticleEditorScene::PreRender()
{
}

void ParticleEditorScene::Render()
{
	if (data.isAdditive)
		STATE->AdditiveBegin();
	else
		STATE->AlphaBegin();

	instanceBuffer->IASetBuffer(1);

	STATE->DepthWriteMaskZero();

	quad->RenderInstanced(drawCount);

	STATE->AlphaEnd();
	STATE->DepthEnable();
}

void ParticleEditorScene::PostRender()
{
}

void ParticleEditorScene::UpdatePhysics()
{
	drawCount = 0;

	for (ParticleInfo& info : particleInfos)
	{
		if (info.startTime > lifeTime)
			continue;


		info.velocity += info.acceleration * Time::Delta();

		info.transform.translation += info.velocity * info.speed * Time::Delta();

		info.transform.rotation.z += info.angularVelocity * Time::Delta();

		if (data.isBillboard)
		{
			Vector3 rot = CAMERA->rotation;

			rot.z = info.transform.rotation.z;

			info.transform.rotation = rot;
		}

		float timeScale = (lifeTime - info.startTime) / (data.duration - info.startTime);
		 
		info.transform.scale = LERP(info.startScale, info.endScale, timeScale);

		info.transform.Update();

		instanceData[drawCount++].transfrom = XMMatrixTranspose(info.transform.GetWorld());
	}
	instanceBuffer->UpdateVertex(instanceData.data(), drawCount);

}

void ParticleEditorScene::UpdateColor()
{
	float timeScale = lifeTime / data.duration;

	Vector4 color;
	color.x = LERP(data.startColor.x, data.endColor.x, timeScale);
	color.y = LERP(data.startColor.y, data.endColor.y, timeScale);
	color.z = LERP(data.startColor.z, data.endColor.z, timeScale);
	color.w = LERP(data.startColor.w, data.endColor.w, timeScale);

	quad->GetMaterial()->GetBuffer()->data.diffuse = color;
}

void ParticleEditorScene::Init()
{
	lifeTime = 0.0f;
	drawCount = 0;
	data.count = particleCount;

	 instanceData.resize(data.count);
	particleInfos.resize(data.count);

	for (ParticleInfo& info : particleInfos)
	{
		info.transform.translation = Random(data.minStartPos,        data.maxStartPos);
		info.velocity              = Random(data.minVelocity,        data.maxVelocity);
		info.acceleration          = Random(data.minAcceleration,    data.maxAcceleration);
		info.startScale            = Random(data.minStartScale,      data.maxStartScale);
		info.endScale              = Random(data.minEndScale,        data.maxEndScale);
		info.speed                 = Random(data.minSpeed,           data.maxSpeed);
		info.angularVelocity       = Random(data.minAngularVelocity, data.maxAngularVelocity);
		info.startTime             = Random(data.minStartTime,       data.maxStartTime);

		info.velocity.Normalize();
	}
}

void ParticleEditorScene::Save(string file)
{
}

void ParticleEditorScene::Load(string file)
{
}

void ParticleEditorScene::SaveDialog()
{
}

void ParticleEditorScene::LoadDialog()
{
}

void ParticleEditorScene::EditTexture()
{
}
