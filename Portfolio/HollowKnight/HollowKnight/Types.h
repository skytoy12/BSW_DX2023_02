#pragma once
#include "Framework/Math/Vector2.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define UP_VECTOR Vector2(0.0f, 1.0f)
#define DOWN_VECTOR Vector2(0.0f, -1.0f)
#define RIGHT_VECTOR Vector2(1.0f, 0.0f)
#define LEFT_VECTOR Vector2(-1.0f, 0.0f)

#define RED             {1.0f, 0.0f, 0.0f, 1.0f}
#define GREEN           {0.0f, 1.0f, 0.0f, 1.0f}
#define BLUE            {0.0f, 0.0f, 1.0f, 1.0f}
#define WHITE           {1.0f, 1.0f, 1.0f, 1.0f}
#define BLACK           {0.0f, 0.0f, 0.0f, 1.0f}
#define GREY            {0.5f, 0.5f, 0.5f, 1.0f}

#define PI 3.141592
#define GRAVITY 0.098f

#define RADIAN(n) n * (XM_PI / 180)

#define DEVICE Device::GetInstance()->GetDevice()
#define DC Device::GetInstance()->GetDC()

#define Vector3 XMFLOAT3

#define SAMPLER StateManager::GetInstance()->GetSampler()
#define ALPHA StateManager::GetInstance()->GetAlpha()
#define ADDITIVE StateManager::GetInstance()->GetAdditive()
#define BLEND StateManager::GetInstance()->GetBlendSTate()

#define KEY_UP(k) InputManager::GetInstance()->Up(k)
#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)

#define MOUSE_POS InputManager::GetInstance()->GetMousePos()
#define W_MOUSE_POS Camera::GetInstance()->GetWorldMousePos()
#define S_MOUSE_POS InputManager::GetInstance()->GetScreenMousePos()

#define DELTA_TIME Timer::GetInstance()->GetDeltaTime()

#define ADD_VS(k) ShaderManager::GetInstance()->AddVS(k)
#define ADD_PS(k) ShaderManager::GetInstance()->AddPS(k)
#define ADD_SRV(k) SRVManager::GetInstance()->Add_SRV(k)

#define RECT(c) static_pointer_cast<RectCollider>(c)
#define CIRCLE(c) static_pointer_cast<CircleCollider>(c)

#define WORLD GetTransform()->GetWorldPosition()

#define EFFECT_LPLAY(n,p) EffectManager::GetInstance()->LeftPlay(n,p)
#define EFFECT_RPLAY(n,p) EffectManager::GetInstance()->RightPlay(n,p)

#define EFFECT_S(n,p) EffectManager::GetInstance()->SetScale(n,p)
#define EFFECT_R(n,p) EffectManager::GetInstance()->SetAngle(n,p)
#define EFFECT_T(n,p) EffectManager::GetInstance()->SetPosition(n,p)


#define SOUND Sound::GetInstance()
#define CAMERA Camera::GetInstance()

#define SCENE SceneManager::GetInstance()

#define LERP(s,e,t) s + (e - s)*t

using CallBack = function<void(void)>;

struct Hit_Result
{
	bool isCollision = false;
	vector<Vector2> contact;
};

struct PlayerInfo
{
	int hp;
	int mp;
};

struct BrickInfo
{
	Vector2 pos;
	Vector2 Scale;
};