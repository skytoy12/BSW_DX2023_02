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
	////////SetEvent////////
	clips[RIFLEFIRE]->SetEndEvent(bind(&Soldier::RifleFire, this), 0.7f);
	clips[SHOTGUNFIRE]->SetEndEvent(bind(&Soldier::ShotGunFire, this), 0.7f);
	////////////////////////

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
	if(curWeapon == SHOTGUN)
		firePoint->translation = shotGun->GetGlobalPosition() + shotGun->Forward() * 4.5f + shotGun->Up() * 0.5f;
	else if(curWeapon == RIFLE)
		firePoint->translation = rifle->GetGlobalPosition() + rifle->Backward() * 3.0f + rifle->Up() * 1.2f;
	


	//if (KEY_DOWN('1'))
	//	PlayClip(0, animSpeed, takeTime);

	if (KEY_DOWN('1'))
		curWeapon = SHOTGUN;

	if (KEY_DOWN('2'))
		curWeapon = RIFLE;

	
	if (shotGun->GetIsAttack() == false && rifle->GetIsAttack() == false);
		Move();

	SetAnim();
	SetGunAnim();
	Delay();


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

	ImGui::Text("SGAttack : %d", shotGun->GetIsAttack());

	ImGui::Text("gunPos = %f, %f, %f", shotGun->GetGlobalPosition().x, shotGun->GetGlobalPosition().y, shotGun->GetGlobalPosition().z);

	ImGui::Text("curPos = %f, %f, %f", curPos.x, curPos.y, curPos.z);
	ImGui::Text("oldPos = %f, %f, %f", oldPos.x, oldPos.y, oldPos.z);

	ImGui::Text("destination = %f, %f, %f", destination.x, destination.y, destination.z);
}

void Soldier::PostRender()
{
	Debug();
	shotGun->Debug();
	//rifle->Debug();
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
	rifle->SetOrigin(firePoint->GetGlobalPosition());

	if (rifle->GetIsAttack() == true)
	{
		moveSpeed = 0.0f;
		rotDamping = 20.0f;
		SetAngle(bulletDestination);
		SetClip(SHOTGUNFIRE);
	}
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
	{
		if (curWeapon == SHOTGUN)
			SetShotGunRun();
		else if (curWeapon == RIFLE)
			SetRifleRun();
	}
	else if (curState == IDLE)
	{
		if (curWeapon == SHOTGUN)
			SetShotGunIdle();
		else if (curWeapon == RIFLE)
			SetRifleIdle();
	}
	else if (curState == SHOTGUNFIRE)
		SetShotGunFire();
	else if (curState == RIFLEFIRE)
		SetRifleFire();
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

void Soldier::SetShotGunFire()
{
	if (shotGun->rotation.x == XMConvertToRadians(-100))
		return;
	if (curWeapon != SHOTGUN)
		return;

	shotGun->rotation.x = XMConvertToRadians(-100);
	shotGun->rotation.y = XMConvertToRadians(-22);
	shotGun->rotation.z = XMConvertToRadians(308);

	shotGun->translation = { 0.160f, 0.450f, -0.010f };
}

void Soldier::SetRifleIdle()
{
	if (shotGun->rotation.x == XMConvertToRadians(116))
		return;
	if (curWeapon != RIFLE)
		return;

	rifle->rotation.x = XMConvertToRadians(116);
	rifle->rotation.y = XMConvertToRadians(46);
	rifle->rotation.z = XMConvertToRadians(-41);

	rifle->translation = { -0.430f, 1.660f, 0.330f };
}

void Soldier::SetRifleRun()
{
	if (shotGun->rotation.x == XMConvertToRadians(86))
		return;
	if (curWeapon != RIFLE)
		return;

	rifle->rotation.x = XMConvertToRadians(86);
	rifle->rotation.y = XMConvertToRadians(-45);
	rifle->rotation.z = XMConvertToRadians(-116);
	
	rifle->translation = { -1.160f, 1.370f, -0.240f };
}

void Soldier::SetRifleFire()
{
	if (shotGun->rotation.x == XMConvertToRadians(94))
		return;
	if (curWeapon != RIFLE)
		return;

	rifle->rotation.x = XMConvertToRadians(94);
	rifle->rotation.y = XMConvertToRadians(41);
	rifle->rotation.z = XMConvertToRadians(-41);

	rifle->translation = { -0.940f, 1.560f, 0.230f };
}

void Soldier::SetGunAttack(bool value)
{
	if (curWeapon == RIFLE)
		rifle->SetIsAttack(value);

	if (curWeapon == SHOTGUN)
		shotGun->SetIsAttack(value);

}

void Soldier::SetAnim()
{
	if (isMove() == true && shotGun->GetIsAttack() == false)
	{
		rotDamping = 5.0f;
		SetAngle(destination);
		SetClip(RUN);
	}
	else
	{
		if (shotGun->GetIsAttack() == true || rifle->GetIsAttack() == true || shotGun->GetIsAttack() == true)
			return;
		SetClip(IDLE);
	}
}

void Soldier::SetGunAnim()
{
	if (shotGun->GetIsAttack() == true)
		SetClip(SHOTGUNFIRE);

	if (rifle->GetIsAttack() == true)
		SetClip(RIFLEFIRE);
}

void Soldier::AttackTimeZero()
{
	rifle->SetIsAttackTime(0.0f);
	shotGun->SetIsAttackTime(0.0f);
}

void Soldier::ShotGunFire()
{
	if (curWeapon != SHOTGUN)
		return;
	shotGun->SetIsAttackTime(0.0f);
	shotGun->SetBulletActive(true);
	//Vector3 dir = bulletDestination - firePoint->translation;
	//dir.y = firePoint->translation.y;
	Vector3 dir = shotGun->Forward();
	shotGun->SetDir(dir);
	shotGun->Update();
	shotGun->Fire();
	shotGun->SetIsAttack(true);
}

void Soldier::RifleFire()
{
	if (curWeapon != RIFLE)
		return;

	//Vector3 dir = bulletDestination - firePoint->translation;
	//dir.y = firePoint->translation.y;
	Vector3 dir = rifle->Forward() * -1;
	rifle->SetDir(dir);
	rifle->Update();
	rifle->Fire();
	if (attackDelay > 0.1f)
	{
		rifle->SetBulletActive(true);
		rifle->BulletNumPlus();
	}
	rifle->SetIsAttack(true);
	attackDelay = 0.0f;
}

void Soldier::Delay()
{
	if (shotGun->GetIsAttack() == true || rifle->GetIsAttack() == true)
	{
		attackDelay += Time::Delta();
	}
}

void Soldier::SetClip(SoldierState type)
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
