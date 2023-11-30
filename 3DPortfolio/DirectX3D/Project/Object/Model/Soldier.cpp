#include "Framework.h"
#include "Soldier.h"

Soldier::Soldier()
	: ModelAnimator("EliteFederationSoldier")
{
	ReadClip("Rifle/Rifle Idle");
	ReadClip("Rifle/Rifle Run");
	ReadClip("Rifle/Rifle Walk");
	ReadClip("Rifle/RifleFire");
	ReadClip("Rifle/ShotGunFire");

	ReadClip("Idle/Breathing Idle");
	ReadClip("Idle/Running");
	ReadClip("Idle/Walking");

	CreateTexture();
	reader->GetMaterials()[0]->SetDiffuseMap(L"Model/EliteFederationSoldier/elite_pmc_lowerbody_a_col.png");

	///////// shot gun /////////
	gunPos = new Transform();
	shotGun = new ShotGun("ShotGun");
	firePoint = new ColliderSphere(0.5f);
	shotGun->SetParent(gunPos);
	shotGun->scale *= 2.0f;
	SetShotGunIdle();
	///////////////////////////
	///////// rifle /////////
	rifle = new Rifle("M4");
	rifle->SetParent(gunPos);
	rifle->scale *= 0.3f;
	/////////////////////////

}

Soldier::~Soldier()
{
	delete shotGun;
	delete rifle;
	delete gunPos;
	delete firePoint;
}

void Soldier::Update()
{
	ModelAnimator::Update();
	Transform::Update();
	ShotGunUpdate();
	RifleUpdate();
	gunPos->Update();
	firePoint->Update();
	firePoint->translation = shotGun->GetGlobalPosition() + shotGun->Forward() * 4.5f + shotGun->Up() * 0.5f;


	//if (KEY_DOWN('1'))
	//	PlayClip(0, animSpeed, takeTime);

	if (KEY_DOWN('1'))
		curWeapon = SHOTGUN;

	if (KEY_DOWN('2'))
		curWeapon = RIFLE;

	
	if (shotGun->GetIsAttack() == false)
		Move();


	if (isMove() == true)
	{
		rotDamping = 5.0f;
		SetAngle(destination);
		SetClip(RUN);
	}
	else
	{
		SetClip(RUN);
	}

	UpdateGunPos();
}

void Soldier::Render()
{
	ModelAnimator::Render();
	if (curWeapon == SHOTGUN)
		shotGun->Render();

	else if (curWeapon == RIFLE)
		rifle->Render();

	firePoint->Render();


}

void Soldier::Debug()
{
	ModelAnimator::reader->Debug();
	ModelAnimator::Debug();

	ImGui::Text("gunPos = %f, %f, %f", shotGun->GetGlobalPosition().x, shotGun->GetGlobalPosition().y, shotGun->GetGlobalPosition().z);

	ImGui::Text("curPos = %f, %f, %f", curPos.x, curPos.y, curPos.z);
	ImGui::Text("oldPos = %f, %f, %f", oldPos.x, oldPos.y, oldPos.z);

	ImGui::Text("destination = %f, %f, %f", destination.x, destination.y, destination.z);
}

void Soldier::PostRender()
{
	Debug();
	shotGun->Debug();
	rifle->Debug();
}

void Soldier::ShotGunUpdate()
{
	if (curWeapon != SHOTGUN)
		return;

	shotGun->Update();
	shotGun->SetOrigin(firePoint->GetGlobalPosition());

	if (shotGun->GetIsAttack() == true)
	{
		moveSpeed = 0.0f;
		rotDamping = 20.0f;
		SetAngle(bulletDestination);
		SetClip(SHOTGUNFIRE);
	}
}

void Soldier::RifleUpdate()
{
	if (curWeapon != RIFLE)
		return;

	rifle->Update();
}

void Soldier::SetAngle(Vector3 dir)
{
	Vector3 temp = this->Forward();
	temp.y = 0;

	Vector3 dir2 = this->GetGlobalPosition();
	//Vector3 dir3 = (dir1 - dir2).GetNormalized();
	Vector3 dir3 = dir - dir2;
	dir3.y = 0;

	Vector3 a = temp;
	Vector3 b = dir3;

	Vector3 isLeft = Vector3::Cross(a, b);

	float AdotB = Vector3::Dot(temp, dir3);
	float length = temp.Length() * dir3.Length();
	float thepta = 0.0f;

	if (length != 0.0f)
	{
		 thepta = acos(AdotB / length);

	}
	
	if (isnan(thepta))
		return;

	if (isLeft.y >= 0.0f)
	{
		float angle = this->rotation.y + thepta - XM_PI;

		this->rotation.y = LERP(this->rotation.y, angle, rotDamping * Time::Delta());
	}
	if (isLeft.y < 0.0f)
	{
		float angle = this->rotation.y - thepta + XM_PI;

		this->rotation.y = LERP(this->rotation.y, angle, rotDamping * Time::Delta());
	}

}



void Soldier::Move()
{
	int temp1 = abs((int)destination.x - (int)this->translation.x);
	int temp2 = abs((int)destination.x - (int)this->translation.x);
	int temp3 = abs((int)destination.x - (int)this->translation.x);

	if (temp1 == 0 && temp2 == 0 && temp3 == 0)
		return;

	Vector3 dir = destination - this->translation;
	if(dir.Length() != 0.0f)
		dir = dir.GetNormalized();

	if (isnan(dir.x) || isnan(dir.y) || isnan(dir.z))
		return;
	
	translation += dir * moveSpeed * Time::Delta();
}



void Soldier::UpdateGunPos()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:RightHand");

	gunPos->GetWorld() = GetTransformByNode(nodeIndex) * world;

	if (curState == RUN)
		SetShotGunRun();
	else if (curState == IDLE)
		SetShotGunIdle();
}

void Soldier::SetShotGunIdle()
{
	if (shotGun->rotation.x == XMConvertToRadians(-68))
		return;
	if (curWeapon != SHOTGUN)
		return;
	shotGun->rotation.x = XMConvertToRadians(-68);
	shotGun->rotation.y = XMConvertToRadians(4);
	shotGun->rotation.z = XMConvertToRadians(-93);

	shotGun->translation = { 0.130f, 0.090f, -0.150f };
}

void Soldier::SetShotGunRun()
{
	if (shotGun->rotation.x == XMConvertToRadians(-78))
		return;
	if (curWeapon != SHOTGUN)
		return;

	shotGun->rotation.x = XMConvertToRadians(-78);
	shotGun->rotation.y = XMConvertToRadians(0);
	shotGun->rotation.z = XMConvertToRadians(-104);

	shotGun->translation = { -0.070f, 0.280f, -0.090f };
}

void Soldier::ShotGunFire()
{
	if (curWeapon != SHOTGUN)
		return;
	shotGun->SetIsAttackTime(0.0f);
	shotGun->SetBulletActive(true);
	Vector3 dir = bulletDestination - firePoint->translation;
	shotGun->SetDir(dir);
	shotGun->Fire();
	shotGun->SetIsAttack(true);
}

void Soldier::SetClip(SoliderState type)
{
	if (type == curState)
		return;
	curState = type;
	oldState = curState;

	PlayClip(curState);
}

bool Soldier::isMove()
{
	oldPos = curPos;
	Transform::UpdateWorld();
	curPos = this->GetGlobalPosition();

	float a = abs(oldPos.x - curPos.x);
	float b = abs(oldPos.y - curPos.y);
	float c = abs(oldPos.z - curPos.z);

	if (a <= FLT_EPSILON && b <= FLT_EPSILON && c <= FLT_EPSILON)
		return false;
	else
		return true;
}
