#include "Framework.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(string file)
{
	Load(file);

	instanceData.resize(particleData.count);

	instanceBuffer = new VertexBuffer(instanceData);

	Init();
}

ParticleSystem::~ParticleSystem()
{
	delete quad;
	delete instanceBuffer;
}

void ParticleSystem::Update()
{
	if (!IsActive())
		return;

	lifeTime += Time::Delta();

	UpdatePhysics();
	UpdateColor();

	quad->Update();

	if (lifeTime > particleData.duration)
	{
		if (particleData.isLoop)
			Init();
		else
			Stop();
	}
}

void ParticleSystem::Render()
{
	if (!IsActive())
		return;

	if (particleData.isAdditive)
		STATE->AdditiveBegin();
	else
		STATE->AlphaBegin();

	instanceBuffer->IASetBuffer(1);

	STATE->DepthWriteMaskZero();

	quad->RenderInstanced(drawCount);

	STATE->AlphaEnd();
	STATE->DepthEnable();
}

void ParticleSystem::Play(Vector3 pos, Vector3 rot)
{
	quad->IsActive() = true;

	quad->translation = pos;
	quad->rotation    = rot;

	Init();
}

void ParticleSystem::Stop()
{
	quad->IsActive() = false;
}

void ParticleSystem::UpdatePhysics()
{
	drawCount = 0;

	for (ParticleInfo& info : particleInfos)
	{
		if (info.startTime > lifeTime)
			continue;


		info.velocity += info.acceleration * Time::Delta();

		info.transform.translation += info.velocity * info.speed * Time::Delta();

		info.transform.rotation.z += info.angularVelocity * Time::Delta();

		if (particleData.isBillboard)
		{
			Vector3 rot = CAMERA->rotation;

			rot.z = info.transform.rotation.z;

			info.transform.rotation = rot;
		}

		float timeScale = (lifeTime - info.startTime) / (particleData.duration - info.startTime);

		info.transform.scale = LERP(info.startScale, info.endScale, timeScale);

		info.transform.Update();

		//instanceData[drawCount].color.x = Random(0.0f, 1.0f);
		//instanceData[drawCount].color.y = Random(0.0f, 1.0f);
		//instanceData[drawCount].color.z = Random(0.0f, 1.0f);
		instanceData[drawCount++].transfrom = XMMatrixTranspose(info.transform.GetWorld());
	}
	instanceBuffer->UpdateVertex(instanceData.data(), drawCount);

}

void ParticleSystem::UpdateColor()
{
	float timeScale = lifeTime / particleData.duration;

	Vector4 color;
	color.x = LERP(particleData.startColor.x, particleData.endColor.x, timeScale);
	color.y = LERP(particleData.startColor.y, particleData.endColor.y, timeScale);
	color.z = LERP(particleData.startColor.z, particleData.endColor.z, timeScale);
	color.w = LERP(particleData.startColor.w, particleData.endColor.w, timeScale);

	quad->GetMaterial()->GetBuffer()->data.diffuse = color;
}

void ParticleSystem::Init()
{
	lifeTime = 0.0f;
	drawCount = 0;
	particleData.count = particleCount;

	instanceData.clear();
	particleInfos.clear();

	instanceData.resize(particleData.count);
	particleInfos.resize(particleData.count);

	UINT count = 0;

	for (ParticleInfo& info : particleInfos)
	{
		info.transform.translation = Random(particleData.minStartPos, particleData.maxStartPos);
		info.velocity = Random(particleData.minVelocity, particleData.maxVelocity);
		info.acceleration = Random(particleData.minAcceleration, particleData.maxAcceleration);
		info.startScale = Random(particleData.minStartScale, particleData.maxStartScale);
		info.endScale = Random(particleData.minEndScale, particleData.maxEndScale);
		info.speed = Random(particleData.minSpeed, particleData.maxSpeed);
		info.angularVelocity = Random(particleData.minAngularVelocity, particleData.maxAngularVelocity);
		info.startTime = Random(particleData.minStartTime, particleData.maxStartTime);

		info.velocity.Normalize();

		instanceData[count].color.x = Random(0.0f, 1.0f);
		instanceData[count].color.y = Random(0.0f, 1.0f);
		instanceData[count].color.z = Random(0.0f, 1.0f);
		count++;
	}
}


void ParticleSystem::Load(string file)
{
	BinaryReader* data = new BinaryReader(file);

	wstring diffisePath = data->ReadWString();

	quad = new Quad();

	quad->GetMaterial()->SetShader(L"18Particle");
	quad->GetMaterial()->SetDiffuseMap(diffisePath);

	ParticleData* temp = new ParticleData();

	data->ReadData((void**)&temp, sizeof(ParticleData));

	particleData = *temp;

	particleCount = particleData.count;

	delete temp;
	delete data;
}